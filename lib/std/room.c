#include <type.h>

inherit obje OBJECT;
inherit cont CONTAINER;
inherit M_FAKE_OBJECT;

static mapping exits;
static mapping hidden_exits;
static string  area;
static int last_exit;

void setup( void );

void create( void ) {
  obje::create();
  cont::create();
  add_event( "body_enter" );
  add_event( "body_leave" );
  add_event( "body_look" );
  add_event( "body_look_at" );
  add_event( "room_message" );
  EVENT_D->subscribe_event( "clean_up" );
  exits = ([]);
  hidden_exits = ([]);
  last_exit = 0;
  setup();
}

void set_area( string str ) {
  area = str;
}

string query_area( void ) {
  return area;
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

void add_hidden_exit( string direction, string file ) {
  hidden_exits += ([ direction : file ]);
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

string query_desc( varargs int brief ) {
  string text;
  int i;

  if(!brief) brief = 0;
  text = query_brief();

  text += " %^CYAN%^[ exits: ";

  if( !exits || map_sizeof( exits ) == 0 ) {
    text += "none ";
  } else {
    for( i = 0; i < map_sizeof( exits ); i++ ) {
      text += map_indices(exits)[i] + " ";
    }
  }

  text += "]%^RESET%^\n";

  text += query_long();

  text += "\n";

  if( inventory && sizeof( inventory ) > 1 ) {
    /* There is something in the room */

    text += "\nYou see:\n";

    for( i = 0; i < sizeof( inventory ); i++ ) {
      if( !inventory[i]->is_living() ) {
	if( !inventory[i]->query_brief() 
	    || inventory[i]->query_brief() == "" ) {
	  if( !inventory[i]->query_adj()
	      || inventory[i]->query_adj() == "" ) {
	    text += "  " + article( inventory[i]->query_id() ) + " " + inventory[i]->query_id() + "\n";
	  } else {
	    text += "  " + article( inventory[i]->query_adj() ) + " " + inventory[i]->query_adj() + " " + inventory[i]->query_id() + "\n";
	  }
	} else {
	  text += "  " + inventory[i]->query_brief() + "\n";
	}
      }
    }

    for( i = 0; i < sizeof( inventory ); i++ ) {
      if( inventory[i]->is_living() ) {
        mixed x;
        if( inventory[i] == this_player() )
          continue;
        x = inventory[i]->query_idle();
        if( x && x > 60 ) {
          text += "  " + inventory[i]->query_brief() 
                  + " [idle" + format_idle_time( inventory[i]->query_idle() ) + "]\n";
        } else {
          text += "  " + inventory[i]->query_brief() + "\n";
        }
      }
    }
  }
  return( text );
}

void tell_room( object originator, string str, varargs mixed obj...) {
  int i;
  
  if( !inventory && sizeof( inventory ) > 0 ) {
    return;
  }
  for( i = 0; i < sizeof( inventory ); i++ ) {
    if( !inventory[i] )
      continue;
    if( originator != inventory[i] && member_array(inventory[i], obj ) == -1 ) {
      if( inventory[i]->is_living() ) {
        inventory[i]->message( capitalize( str ) );
      }
      inventory[i]->outside_message( capitalize( str ) );
    }
  }
}

string body_exit( object who, string dir ) {
  int i;
  string error;
  
  if( !query_exit( dir ) && !query_hidden_exit( dir ) ) {
    write( "You can't go " + dir + ".\n" );
    return( nil );
  } 
  
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
    tell_room( who, capitalize( who->query_id() ) + " leaves " + dir + ".\n" );
    error = catch( who->move( query_exit( dir ) ) );
    last_exit = time();
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
    tell_room( who, capitalize( who->query_id() ) + " leaves " + dir + ".\n" );
    error = catch( who->move( query_hidden_exit( dir ) ) );
    last_exit = time();
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
  who->query_environment()->tell_room( who, capitalize( who->query_id() ) + " enters.\n" );
  return( nil );
}

void destruct( void ) {
  int i;
  for( i = 0; i < sizeof( inventory ); i++ ) {
    inventory[i]->destruct();
  }
  EVENT_D->unsubscribe_event( "clean_up" );
  destruct_object( this_object() );
}

void event_clean_up( void ) {
  int i;


  if( time() - last_exit < 60 * 15 ) 
     return;

  for( i = 0; i < sizeof( inventory ); i++ ) {
    if( !inventory[i] )
      continue;
    if( inventory[i]->is_player() || inventory[i]->is_possessed() )
      return;
  }

  destruct();
}
