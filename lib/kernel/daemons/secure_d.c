#define PLAYER 0
#define WIZ    1
#define ADMIN  2

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

void restore_me( void ) {
  restore_object( "/kernel/daemons/data/secure_d.o" );
}

void save_me( void ) {
  save_object( "/kernel/daemons/data/secure_d.o" );
}

void create( void ) {
  privs =  ([]);
  restore_me();
  DRIVER->register_secure_d();
}

void make_wizard( string name ) {
  object player;

  if( previous_object()->base_name() != "/kernel/cmds/admin/mkwiz" ) {
    error( "Hey! No cheating!\n" );
  }

  name = lowercase( name );
  if( file_exists( "/data/players/" + name + ".o" ) ) {
    privs[name] = WIZ;
    player = USER_D->find_player( name );
    if( !player ) {
      /* Player not active now, load him in and add his paths. */
      player = clone_object( "/std/player" );
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

  name = lowercase( name );
  if( file_exists( "/data/players/" + name + ".o" ) ) {
    privs[name] = ADMIN;
    player = USER_D->find_player( name );
    if( !player ) {
      /* Player not active now, load him in and add his paths. */
      player = clone_object( "/std/player" );
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
  if( privs[name] == ADMIN )
    return 1;
  return 0;
}

int query_wiz( string name ) {
  if( privs[name] == ADMIN || privs[name] == WIZ )
    return 1;
  return 0;
}

int query_priv( string name ) {
  if( map_sizeof(privs) == 0 )
  	make_admin( name );
  if(!privs[name])
    return 0;
  return( privs[name] );
}

#define ROOT_OVERRIDE ({ "/std/user.c", "/std/player.c" })

string owner_file(string file) {
  string * parts;
  string tmp;
  int i,sz;

  argcheck(file, 1, "string");

  file = normalize_path(file, previous_program()+"../");

  if( sizeof( ({ file }) & ROOT_OVERRIDE ) ) {
    return "root";
  }

  parts = explode(file, "/");

  switch(parts[0]) {
    case "kernel"  :
      return "kernel";
      break;
    case "daemons" :
    case "sys"     :
      return "system";
      break;
    case "wiz"     :
    case "domains" :
      if(sizeof(parts) > 1) {
        return parts[1];
      }
      break;
  }
  return "nobody";
}

