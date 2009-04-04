#include <type.h>

inherit cont CONTAINER;
inherit M_FAKE_OBJECT;

static mapping exits;
static mapping hidden_exits;
static mapping areas;
static mapping room_commands;
static int last_exit;
static mapping wanted_objects;
private int configured;

void setup( void );

void create( void ) {
  cont::create();
  add_event( "body_enter" );
  add_event( "body_leave" );
  add_event( "body_look" );
  add_event( "body_look_at" );
  add_event( "room_message" );
  EVENT_D->subscribe_event( "clean_up" );
  EVENT_D->subscribe_event( "reset" );
  exits = ([]);
  hidden_exits = ([]);
  areas = ([]);
  room_commands = ([]);
  last_exit = 0;
  setup();
  configured = 1;
}

void add_area( string str ) {
  areas += ([ str : 1 ]);
}

int query_in_area( string str ) {
  if ( areas[str] ) return 1;
  else return 0;
}

string *query_areas() {
  return map_indices( areas );
}

void set_exits( mapping ex ) {
  exits = ex;
}

void set_hidden_exits( mapping ex ) {
  hidden_exits = ex;
}

void add_exit( string direction, string file ) {
  exits += ([ direction : file ]);
}

void remove_exit( string direction ) {
  exits[direction] = nil;
}

void add_hidden_exit( string direction, string file ) {
  hidden_exits += ([ direction : file ]);
}

void remove_hidden_exit( string direction ) {
  hidden_exits[direction] = nil;
}

void set_exit_msg( string ext, string msg ) {

}

mapping query_exits( void ) {
  return(exits);
}              

mapping query_hidden_exits( void ) {
  return(hidden_exits);
}              

string *query_exit_indices( void ) {
  return( map_indices( exits ) );
}

string *query_hidden_exit_indices( void ) {
  return( map_indices( hidden_exits ) );
}

string query_exit( string direction ) {
  return( exits[direction] );
}

string query_hidden_exit( string direction ) {
  return( hidden_exits[direction] );
}

/* Attempts to find the actual room object attached to a given exit.
  Will compile it if necessary.
  Cerihan - 3/13/09
*/
object query_exit_room( string direction ) {
  string exit;
  object qroom;

  exit = query_exit( direction );
  if( !exit ) return nil;

  qroom = find_object( exit );
  if ( !qroom )
    qroom = compile_object( exit );

  return qroom;
}

string query_desc( varargs int brief ) {
  string text;
  int i;
  object * inventory;

  if(!brief) brief = 0;
  text = "%^ROOM_NAME%^" + query_brief() + "%^RESET%^";

  text += " %^ROOM_EXIT%^[ exits: ";

  if( !exits || map_sizeof( exits ) == 0 ) {
    text += "none ";
  } else {
    for( i = 0; i < map_sizeof( exits ); i++ ) {
      text += map_indices(exits)[i] + " ";
    }
  }

  text += "]%^RESET%^\n";

  text += "%^ROOM_DESC%^" + query_long() + "%^RESET%^";

  text += "\n";

  inventory = query_inventory();

  if( inventory && sizeof( inventory ) > 1 ) {
    /* There is something in the room */

    text += "\nYou see:\n";

    for( i = 0; i < sizeof( inventory ); i++ ) {
      if( !inventory[i]->is_living() ) {
	  text += "  %^OBJ_BRIEF%^" + capitalize( inventory[i]->query_brief() ) + "%^RESET%^\n";
      }
      else {
        mixed x;
        string pc;
        if( inventory[i] == this_player() )
          continue;
        x = inventory[i]->query_idle();
        pc = inventory[i]->is_player() ? "%^PLAYER%^" : "%^NPC_FRIENDLY%^";
        if( x && x > 60 ) {
          text += "  " + pc + capitalize( inventory[i]->query_brief() ) 
                  + " [idle" + format_idle_time( inventory[i]->query_idle() ) + "]%^RESET%^\n";
        } else {
          text += "  " + pc + capitalize( inventory[i]->query_brief() ) + "%^RESET%^\n";
        }
      }
    }
  }
  return( text );
}

void add_room_command( string command, string function ) {
  if (!room_commands[command]) room_commands += ([ command : function ]);
  else room_commands[command] = function;
}

string query_room_command( string command ) {
  return room_commands[command];
}

/*-------------------------------------------------------------------
  void message_room( object originator, string str );
  
  sends a message to the room, designed specificly for non-living
  objects to communicate with the room
*/
void message_room( object originator, string str ) {
  int i, sz;
  object * inventory;

  inventory = query_inventory();

  if( !inventory && sizeof(inventory) > 0 ) {
    return;
  }
  for( i = 0, sz = sizeof(inventory); i < sz; i++ ) {
    if( !inventory[i] ) continue;
    if( originator != inventory[i] ) {
      if( inventory[i]->is_living() ) {
        inventory[i]->message(str);
      }
      inventory[i]->outside_message(str);
    }
  }
}

void tell_room( object originator, string str, varargs mixed obj...) {
  int i;
  object * inventory;

  inventory = query_inventory();

  if( !inventory && sizeof( inventory ) > 0 ) {
    return;
  }
  for( i = 0; i < sizeof( inventory ); i++ ) {
    if( !inventory[i] )
      continue;
    if( originator != inventory[i] && member_array(inventory[i], obj ) == -1 ) {
      if( inventory[i]->is_living() && 
          (!originator ||
          !inventory[i]->query_ignored(originator->query_name())) ) {
        inventory[i]->message( capitalize( str ) );
      }
      inventory[i]->outside_message( capitalize( str ) );
    }
  }
}

string body_exit( object who, string dir ) {
  int i;
  string error;
  string lname;
  string aname;  
  object * inventory;

  if( !query_exit( dir ) && !query_hidden_exit( dir ) ) {
    write( "You can't go " + dir + ".\n" );
    return( nil );
  } 
  
  lname = who->query_proper_name();
  aname = lname;
  if ( !lname ) {
    /* Generic-named NPCs */
    lname = "The " + who->query_id();
    aname = "A " + who->query_id();
  }

  inventory = query_inventory();

  /* there is a normal exit */
  if( query_exit( dir ) ) {
    /* Is there a fake exit? */
    if( query_exit( dir )[0] == '#' ) {
      return( query_exit( dir )[1..] );
    }
    for( i = 0; i < sizeof( inventory ); i++ ) {
      if( inventory[i]->is_blocking( dir ) ) {
	      /* We've got an object blocking the exit! */
        if( !inventory[i]->do_block( who ) ) {
	        inventory[i]->other_action( inventory[i], inventory[i]->query_block_action(), who, dir );
	        return( nil );
	      }
      }
    }
    event( "body_leave", who );
    tell_room( who, lname + " leaves " + dir + ".\n" );
    error = catch( who->move( query_exit( dir ) ) );
    if (who->is_player()) last_exit = time();
  } else if( query_hidden_exit( dir ) ) {
    /* there is a hidden exit */
    if( query_hidden_exit( dir )[0] == '#' ) {
      return( query_hidden_exit( dir )[1..] );
    }
    for( i = 0; i < sizeof( inventory ); i++ ) {
      if( inventory[i]->is_blocking( dir ) ) {
    	/* We've got a monster blocking the exit! */
      	if( inventory[i]->do_block( who ) ) {
	        inventory[i]->other_action( inventory[i], inventory[i]->query_block_action(), who, dir );
	        return( nil );
	      }
      }
    }
    event( "body_leave", who );
    tell_room( who, lname + " leaves " + dir + ".\n" );
    error = catch( who->move( query_hidden_exit( dir ) ) );
    if (who->is_player()) last_exit = time();
  }
  
  
  if( error ) {
    if( SECURE_D->query_wiz( who->query_id() ) == 1 )
      return( "\nConstruction blocks your path.\n" + "Error: " + error);
    else
      return( "\nConstruction blocks your path.\n" );
  }
  
  if( who->is_player() || who->is_possessed() ) {
     mixed desc;
     desc = PARSE_D->parse( "look" );
     if( typeof( desc ) == T_STRING ) {
	write( desc );
     }
  }
  event( "body_enter", who );
  who->query_environment()->tell_room( who, aname + " enters.\n" );
  return( nil );
}

void set_objects(mapping objs) {
  wanted_objects = objs;
  if(!configured) {
    ::set_objects(objs);
  }
}

void destruct( void ) {
  move_or_destruct_inventory();

  EVENT_D->unsubscribe_event( "clean_up" );
  ::destruct();
}

void event_reset( void ) {
  if(wanted_objects) {
    ::set_objects(wanted_objects);
  }
}

void event_clean_up( void ) {
  int i;
  object * inventory;

  if( time() - last_exit < 60 * 15 ) 
     return;

  inventory = query_inventory();
  for( i = 0; i < sizeof( inventory ); i++ ) {
    if( !inventory[i] )
      continue;
    if( inventory[i]->is_player() || inventory[i]->is_possessed() || inventory[i]->no_cleanup() )
      return;
  }

  destruct();
}

void upgraded() {
  ::upgraded();
  if(clone_num() == 0) setup();
}

