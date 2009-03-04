#include <type.h>
inherit "/std/body/size"; /* satch */
/* inherit "/std/modules/m_autoload_filename"; */

static string brief_desc;
string  long_desc;
static object  object_environment;
static string *ids;
static string *adjs;
static int object_size;
string proper_name;
static string *object_commands;
static string detailed_desc;

void create( void ) {
  brief_desc = "";
  ids = ({ "nondescript thing" });
  adjs = ({ });
  OBJECT_D->register_object( this_object() );
}

int is_living( void ) {
  return( 0 );
}

int is_player( void ) {
  return( 0 );
}

void set_id( string str, varargs mixed args...) {
  int i;

  ids = ({ str });
  for( i = 0; i < sizeof( args ); i++ ) {
    ids += ({ (string) args[i] });
  }
}

void add_id( string str, varargs mixed args...) {
  int i;

  if( !ids )
    ids = ({ });

  ids += ({ str });
  for( i = 0; i < sizeof( args ); i++ ) {
    ids += ({ (string) args[i] });
  }
}

void add_ids( string str, varargs mixed args...) {
  int i;

  if( !ids )
    ids = ({ });

  ids += ({ str });
  for( i = 0; i < sizeof( args ); i++ ) {
    ids += ({ (string) args[i] });
  }
}

string query_id( void ) {
  return( ids[0] );
}

string *query_ids( void ) {
  return( ids );
}

int is_id( string id ) {
  int i;
  for( i = 0; i < sizeof( ids ); i++ ) {
    if( ids[i] == id )
      return( 1 );
  }
  return( 0 );
}

void set_adj( string str, varargs mixed args...) {
  int i;

  adjs = ({ str });
  for( i = 0; i < sizeof( args ); i++ ) {
    adjs += ({ (string) args[i] });
  }
}

void add_adj( string str, varargs mixed args...) {
  int i;

  if( !adjs )
    adjs = ({ });
  adjs += ({ str });
  for( i = 0; i < sizeof( args ); i++ ) {
    adjs += ({ (string) args[i] });
  }
}

string *query_adjs( void ) {
  return( adjs );
}

string query_adj( void ) {
  if( sizeof( adjs ) == 0 )
    return( "" );
  return( adjs[0] );
}

int is_adj( string adj ) {
  int i;
  for( i = 0; i < sizeof( adjs ); i++ ) {
    if( adjs[i] == adj )
      return( 1 );
  }
  return( 0 );
}

void set_brief( string str ) {
  brief_desc = str;
}

void set_in_room_desc( string str ) {
  brief_desc = str;
}

string query_in_room_desc( void ) {
  return( brief_desc );
}

string query_brief( void ) {
  if( !brief_desc || brief_desc == "" ) {
    if( !query_adj() || query_adj() == "" ) {
      brief_desc = article( query_id() ) + " " + query_id();
    } else {
      brief_desc = article( query_adj() ) + " " + query_adj() + " " 
	         + query_id();
    }
  }
  return( brief_desc );
}

void set_long( string str ) {
  long_desc = str;
}

string query_long( void ) {
  return( long_desc );
}

void set_proper_name( string name ) {
  proper_name = name;
} 

string query_proper_name( void ) {
  return( proper_name );
}
/*

void set_size( int sz ) {
  object_size = sz;
}

int query_size( void ) {
  return( object_size );
}
*/

object query_environment( void ) {
  return( object_environment );
}

void set_environment( object ob ) {
  object_environment = ob;
}

void destruct( void ) {
  if( object_environment ) 
    object_environment->remove_object( this_object() );

  OBJECT_D->unregister_object( this_object() );
  destruct_object( this_object() );
}

int move( mixed destination ) {
  int err;
  object dest;

  if( !destination )
    return( 0 );
  if( typeof( destination ) == T_STRING ) {
    /* Remove trailing .c */
    if( destination[strlen( destination )-2..] == ".c" )
      destination = destination[..strlen(destination)-3];
    dest = find_object( destination );
    if( !dest )
      dest = compile_object( destination );
  } else {
    dest = destination;
  }

  if( !dest ) {
    return( 0 );
  }

  if( object_environment == dest ) {
    return( 0 );
  }

  err = dest->receive_object( this_object() );

  if( !err || err != 1) {
    write( "Error in move:" + err + "\n" );
    return( 0 );
  }

  if( object_environment ) {
    if( object_environment->is_living() ) {
      if( sizeof( this_object()->query_object_commands() ) > 0 ) {
	string *objcmds;
	int i;

	objcmds = this_object()->query_object_commands();
	for( i = 0; i < sizeof( objcmds ); i++ ) {
	  object_environment->remove_item_command( objcmds[i] );
	}
      }
    }
    object_environment->remove_object( this_object() );
    
  }

  object_environment = dest;

  if( object_environment->is_living() ) {
    if( sizeof( this_object()->query_object_commands() ) > 0 ) {
      string *objcmds;
      int i;
      
      objcmds = this_object()->query_object_commands();
      for( i = 0; i < sizeof( objcmds ); i++ ) {
	object_environment->add_item_command( objcmds[i], this_object() );
      }
    }
  }
  
  
  return( 1 );
}

void add_object_command( string command ) {
  if( !object_commands )
    object_commands = ({ });
  object_commands += ({ command });
}

void remove_object_command( string command ) {
  if( !object_commands )
    object_commands = ({ });
  object_commands -= ({ command });
  
}

string *query_object_commands( void ) {
  if( !object_commands )
    object_commands = ({ });
  return( object_commands );
}

void set_detailed_desc( string desc ) {
	detailed_desc = desc;
}

string query_detailed_desc( void ) {
	return( detailed_desc );
}
