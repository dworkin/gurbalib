#define PLAYER_L 0
#define WIZ_L    1
#define ADMIN_L  2

/* uncomment the line below to get a lot of debug output.. */

/* #define DEBUG_STACK_SECURITY */

#include <trace.h>
#include <privileges.h>

/*
 * During boot, the compiler daemon will not be available yet to
 * include std-kernel.h automatically. However, when this object
 * gets recompiled later, the compiler daemon will be there and
 * automatically include std-kernel.h
 */
#ifndef __KERNEL__
#include <std-kernel.h>
#endif

mapping privs;
mapping domains;

static int restore_me( void ) {
  return restore_object( "/kernel/daemons/data/secure_d.o" );
}

static void save_me( void ) {
  save_object( "/kernel/daemons/data/secure_d.o" );
}

int add_domain( string name ) {
  if( !require_priv( "system" ) ) {
    error( "Illegal call to add_domain" );
  }

  if( !domains[name] ) {
    domains[name] = time();
    return 1;
  } else {
    return 0;
  }
}

int remove_domain( string name ) {
  if( !require_priv( "system" ) ) {
    error( "Illegal call to remove_domain" );
  }

  if( domains[name] != nil ) {
    domains[name] = nil;
    return 1;
  } else {
    return 0;
  }
}

void mkdomains() {
  int i, sz;
  string * names;

  names = get_dir("/domains/*")[0];
  names -= ({ ".", "..", ".svn", ".cvs" });
  for( i = 0, sz = sizeof( names ); i < sz; i++ ) {
    unguarded( "add_domain", names[i] );
  }
}

static void create( void ) {
  privs =  ([]);
  domains = ([]);
  if(!restore_me()) {
    mkdomains();
  }
  DRIVER->register_secure_d();
}

void make_wizard( string name ) {
  object player;

  if( previous_object()->base_name() != "/kernel/cmds/admin/mkwiz" ) {
    error( "Hey! No cheating!\n" );
  }

  if( !require_priv( "system" ) ) {
    error( "Access denied" );
  }

  name = lowercase( name );
  if( file_exists( "/data/players/" + name + ".o" ) ) {
    privs[name] = WIZ_L;
    player = USER_D->find_player( name );
    if( !player ) {
      /* Player not active now, load him in and add his paths. */
      player = clone_object( PLAYER_OB );
      player->set_name( name );
      player->restore_me();
      player->add_cmd_path( "/cmds/wiz" );
      player->save_me();
      destruct_object( player );
    } else {
      player->add_cmd_path( "/cmds/wiz" );
      player->save_me();
    }
    write( capitalize( name ) + " has been made a wizard." );
    save_me();
  } else {
    write( "No such player.\n" );
  }
}

void make_admin( string name ) {
  object player;

  if( !require_priv( "system" ) ) {
    error( "Access denied" );
  }

  name = lowercase( name );
  if( file_exists( "/data/players/" + name + ".o" ) ) {
    privs[name] = ADMIN_L;
    player = USER_D->find_player( name );
    if( !player ) {
      /* Player not active now, load him in and add his paths. */
      player = clone_object( PLAYER_OB );
      player->set_name( name );
      player->restore_me();
      player->add_cmd_path( "/cmds/wiz" );
      player->add_cmd_path( "/kernel/cmds/admin" );
      player->add_channel("dgd");
      player->save_me();
      destruct_object( player );
    } else {
      player->add_cmd_path( "/cmds/wiz" );
      player->add_cmd_path( "/kernel/cmds/admin" );
      player->add_channel("dgd");
      player->save_me();
    }
    write( capitalize( name ) + " has been made an admin." );
    save_me();
  } else {
    write( "No such player.\n" );
  }
}

int query_admin( string name ) {
  if( privs[name] == ADMIN_L )
    return 1;
  return 0;
}

int query_wiz( string name ) {
  if( privs[name] == ADMIN_L || privs[name] == WIZ_L )
    return 1;
  return 0;
}

int query_mortal( string name ) {
  return privs[name] != ADMIN_L && privs[name] != WIZ_L ;
}


int query_priv( string name ) {
  if( map_sizeof(privs) == 0 )
  	unguarded( "make_admin", "name" );
  if(!privs[name])
    return 0;
  return( privs[name] );
}

#define ROOT_OVERRIDE ({ })

/*
 * Do the privileges provided in str contain a root privilege?
 */
int root_priv( string str ) {
  if(
    sscanf( str, "%*s:system:%*s" ) != 0 ||
    sscanf( str, "%*s:kernel:%*s" ) != 0
  ) {
    return 1;
  }
}

/*
 * Do the privileges provided in str include 'game' privileges?
 */
int game_priv( string str ) {
  if(
    sscanf( str, "%*s:game:%*s" ) != 0 
  ) {
    return 1;
  }
}

/*
 * Who 'owns' the file provided as argument? This is the filesystem owner
 * of that file, and is used for things like default privileges
 */
string owner_file(string file) {
  string * parts;
  string tmp;
  int i,sz;

  argcheck(file, 1, "string");

  if( sizeof( ({ file }) & ROOT_OVERRIDE ) ) {
    return "system";
  }

  parts = explode(file, "/");

  switch(parts[0]) {
    case "kernel"  :
      return "kernel";
      break;
    case ""        :
    case "daemons" :
    case "sys"     :
    case "cmds"    :
      return "system";
      break;
    case "std"     :
    case "obj"     :
    case "game"    :
    case "logs"    :
    case "data"    :
      return "game";
      break;
    case "wiz"     :
    case "domains" :
      if(sizeof(parts) > 1) {
        return parts[1];
      } else {
        return "system";
      }
      break;
  }
  return "nobody";
}

/*
 * Determine the privileges of an inheritable
 */
string determine_program_privs( string progname ) {
  return ":" + owner_file( progname ) + ":";
}

/*
 * Determine the privileges for the object with the objectid 'objname'
 */
string determine_obj_privs( string objname ) {
  string name;
  string priv;
  object ob;

  ob = find_object( objname );

  if( !ob ) {
    return ":nobody:";
  }

  if( sscanf( objname, "/sys/obj/user/%*s" ) == 1 ) {
    name = ob->query_name();
    if( !name || name == "" ) {
      priv = "nobody";
    } else {
      priv = name;
      if( query_wiz( name ) ) {
        priv += ":wiz";
      }

      if( query_admin( name ) ) {
        priv += ":system";
      }
    }
  } else {
    priv = owner_file( objname );
  }

  return ":" + priv + ":";
}

int is_domain( string name ) {
  return domains[name] != nil;
}

/*
 * The stack validator, this function is what it is all about..
 *
 * Gets a call_stack, and loops through it to determine the 
 * privileges of all objects and inheritables that brought us
 * to where we are now. It then matches those privileges against
 * the required privilege provided in the priv argument.
 * Optionally, unguarded can be set, which will cause this function
 * to only check the direct caller for privileges.
 */

static int validate_privilege( string spriv, string rpriv ) {
  if( 
    root_priv( spriv ) ||
    ( game_priv( spriv ) && is_domain( rpriv ) ) ||
    ( sscanf( spriv, "%*s:"+rpriv+":%*s" ) != 0 ) 
  ) {
    return 1;
  }
}

int validate_stack( string priv, varargs int unguarded ) {
  int i, sz, deny;
  mixed ** stack;
  string progname;
  string objname;
  string funname;
  string ppriv;
  string opriv;
  mapping cache;

  if(!KERNEL()) {
    return 0;
  }

  if( priv == "*" ) {
    return 1;
  }

  stack = call_trace();
  cache = ([ ]);

  for( i = sizeof( stack ) - 4; ( i >= 0 ) && !deny && ( unguarded < 2 ); i-- ) {

    progname = stack[i][TRACE_PROGNAME];
    objname = stack[i][TRACE_OBJNAME];
    funname = stack[i][TRACE_FUNCTION];

    if( unguarded || ( ( funname == "unguarded" ) && ( sscanf( progname, "/kernel/lib/auto%*s" ) ) ) ) {
      unguarded++;
    }

    if(cache[objname]) {
      opriv = cache[objname];
    } else {
      opriv = determine_obj_privs( objname );
      cache[objname] = opriv;
    }

    ppriv = determine_program_privs( progname );

#ifdef DEBUG_STACK_SECURITY
    console_msg("validate_stack:\n"+
      "*** frame    : " + i + "\n"+
      "*** require  : " + priv + "\n"+
      "*** program  : " + progname + "\n"+
      "**  function : " + funname + "\n"+
      "*** privs    : " + ppriv+"\n"+
      "*** object   : " + objname + "\n"+
      "*** objprivs : " + opriv + "\n"
    );
#endif

    if( !validate_privilege( ppriv, priv ) ) {
      deny++;
    }

    if( !validate_privilege( opriv, priv ) ) {
      deny++;
    }
  }
  return !deny;
}

/*
 * Determine the privilege required for reading the file provided as argument.
 * It does not check at all if that file exists!
 */
string query_read_priv( string file ) {
  string * parts;

  parts = explode( file, "/" );

#ifdef DEBUG_PRIVS
  console_msg("query_read_priv( \""+file+"\" )\n");
#endif

  if( !sizeof( parts ) ) {
    return "*";
  }

  /*
   * domains dir is special. Read access to everything for
   * everyone except for the /domains/<dom>/data dir.
   *
   * daemons dir is special. Read access to everything for
   * everyone except for the /daemons/data dir.
   *
   */
  switch( parts[0] ) {
    case "kernel"  :
      if( sizeof( parts ) > 1 && parts[1] == "data" ) {
        return owner_file( file );
      }
      /* fall through, so no I didn't forget a break here */
    case "domains" :
      if( sizeof( parts ) > 2 && parts[2] == "data") {
        return owner_file( file );
      }
      break;
    case "data" :
      return owner_file( file );
      break;
    case "daemons" :
    case "sys" :
      if(sizeof(parts) > 1 && parts[1] == "data") {
        return owner_file( file );
      }
      break;
    case "wiz" :
      if(sizeof(parts) > 1) {
        return owner_file( file );
      }
      break;
  }

  return "*";
}

/*
 * Determine the privilege required for writing the file provided as
 * argument.
 */
string query_write_priv( string file ) {
#ifdef DEBUG_PRIVS
  console_msg("query_write_priv( \""+file+"\" )\n");
#endif
  return owner_file( file );
}


static void upgraded() {
  if(!domains) {
    domains = ([ ]);
    mkdomains();
  }
}

