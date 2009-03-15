inherit "/std/modules/m_autoload_string";
#include <user.h>
#include <limits.h>

object player;

string user_name;
static int timeout_handle;
object query_player( void );

void create() {
  user_name = "";
}

void open() {
  if( SITEBAN_D->is_banned(query_ip_number(this_object())) ) {
      /* site is banned */
      write_file( "/logs/logins", ctime( time() ) + "\t" + query_ip_number(this_object()) +
         "\t" + "Banned Site\n" );
      send_message( "\nYour site is under an access restriction.\n"+
         "Please email " + ADMIN_EMAIL + " about access from your site.\n" );
      destruct_object( this_object() );
  }
  /* cat_file( "/data/messages/login" ); */
  send_message( "\n" );
  send_message( "Welcome to " + MUD_NAME + ".\n" );
  send_message( "Running " + LIB_NAME + " " + LIB_VERSION + ".\n" );
  send_message( "\n" );
  send_message( "Enter your name : " );
  send_message( 1 );
  timeout_handle = call_out( "login_timeout", 600 );
  player = clone_object( "/std/player" );
  player->set_user( this_object() );
  player->initialize_cmd_path();
  player->initialize_alias();
  player->set_long( "A boring player without a description." );
  write_file( "/logs/logins", ctime( time() ) + "\t" + query_ip_number(this_object()) +
      "\t" +"opening connection\n" );
  player->input_to_object( this_object(), "input_name" );
}

void close( int ld ) {
  string ip;
    
  ip = query_ip_number(this_object());
  if(!ip) ip = "<NO IP>";
  if( ld == 0 ) {
    player->set_linkdead( 1 );
    write_file( "/logs/logins", ctime( time() ) + "\t" + ip +
      "\t\t" + this_object()->query_name() +" disconnects\n" );

  } else {
    if( player ) {
      destruct_object( player );
    }
  }
}

void login_timeout( void ) {
  send_message( "\nTimeout.\n" );
  destruct_object( player );
  destruct_object( this_object() );
}

void quit( void ) {
  string str;
  
  player->save_me();
  LAST_D->add_entry( user_name, 0 );
  USER_D->remove_user( user_name, this_object() );
  if( query_ip_number(this_object()) ) {
      write_file( "/logs/logins", ctime( time() ) + "\t" + query_ip_number(this_object()) +
      "\t" + this_object()->query_name() +" quits\n" );
  } else {
      write_file( "/logs/logins", ctime( time() ) + "\t" +
      "\t\t" + this_object()->query_name() +" LD quits\n" );
  }

  player->destruct();
  destruct_object( this_object() );
}

void put_original( string str ) {
  if( !str || str == "" )
    return;
  send_message( str );
}

void put_message( string str ) {
  string msg;

  if( !str || str == "" )
    return;

  if( query_player()->query_ansi() )
    msg = ANSI_D->parse_colors( str );
  else
    msg = ANSI_D->strip_colors( str );
  send_message( msg );
}

void wrap_message( string str ) {

  string msg;
  string *words;
  string *lines;
  int width;
  int i,j;
  int sz;

  if( !str || str == "" )
    return;

  width = -1;
  /* Get the width from the player */
  if( player ) {
    	catch (width = str2val((string)player->query_env( "width" )));
  }

  if( width < 0 ) width = 78;
  if( width  == 0 ) width = MAX_STRING_SIZE;

  /* Split the string into lines */
  lines = explode( str, "\n" );

  /* Parse each line */
  for( j = 0; j < sizeof( lines ); j++ ) {
    str = lines[j];
    msg = str;
    if( strlen( ANSI_D->strip_colors( str ) ) > width ) {
      sz = 0;

      words = explode( str, " " );
      msg = "";

      for( i = 0; i < sizeof( words ); i++ ) {
   if( strlen( words[i] ) > 4 ) {
     if( strstr( words[i], "%^" ) != -1 ) {
       if( sz == 0 ) {
         sz += strlen( ANSI_D->strip_colors( words[i] ) );
         msg += words[i];
       } else {
         sz += strlen( ANSI_D->strip_colors( words[i] ) ) + 1;
         msg += " " + words[i];
       }
       continue;
     }
   }
   if( sz + strlen( words[i] ) > width ) {
     msg += "\n  ";
     sz = strlen( words[i] ) + 2;
     msg += words[i];
   } else {
     if( sz == 0 ) {
       msg += words[i];
       sz += strlen( words[i] );
     } else {
       msg += " " + words[i];
       sz += strlen( words[i] ) + 1;
     }
   }
      }
    }
    if( query_player()->query_ansi() )
      msg = ANSI_D->parse_colors( msg );
    else
      msg = ANSI_D->strip_colors( msg );
    send_message( msg + "\n" );
  }
}

void receive_message( string message ) {
  rlimits(256; 1000000) {
    player->receive_message( message );
  }
}

void login_user( void ) {
  object usr;
  int i;
  int flag;
  object tmp_player;
  
  send_message( 1 );

  flag = 0;

  usr = USER_D->find_user( user_name );

  if( usr ) {
    send_message( "Already logged in.\n" );
    flag = 1;
    if( usr->query_player()->query_linkdead() == 1 ) {
      send_message( "Reconnecting to linkdead player.\n" );
      tmp_player = usr->query_player();
      usr->set_player( player );
      player = tmp_player;
      usr->quit();
      write_file( "/logs/logins", ctime( time() ) + "\t" + query_ip_number(this_object()) +
         "\t" + this_object()->query_name() +" reconnects\n" );
      player->set_linkdead( 0 );
      player->set_user( this_object() );
      USER_D->add_user( user_name, this_object() );
      player->write_prompt();
      remove_call_out( timeout_handle );
    } else {
      send_message( "Reconnect to the other copy? (y/n) : " );
      player->input_to_object( this_object(), "handle_reconnect" );
    }
  } else {
    player->set_name( user_name );
    USER_D->add_user( user_name, this_object() );
    player->set_brief( capitalize( user_name ) + player->query_title() );
    send_message( "\n" );
    cat_file( "/data/messages/login" );
    send_message( "\n" );
    cat_file( "/data/messages/motd" );
    player->login_player();
    clone_autoload_objects( player->query_autoload_string() );
    player->move( STARTING_ROOM );
    player->simple_action( "$N $vlog in.\n" );
    player->do_look( 0 );
    player->write_prompt();
    remove_call_out( timeout_handle );
    LAST_D->add_entry( user_name, 1 );
    write_file( "/logs/logins", ctime( time() ) + "\t" + query_ip_number(this_object()) +
         "\t" + this_object()->query_name() +" connects\n" );
     
  }
}

void handle_reconnect( string str ) {
  if( !str || str == "" ) {
    send_message( "Please enter y or n : " );
    player->input_to_object( this_object(), "handle_reconnect" );
  } else if( lowercase( str ) == "y" ) {
    object tmp_player;
    int flag;
    int i;
    object usr; 

    usr = USER_D->find_user( user_name );
    if( usr ) {
      flag = 1;
      tmp_player = usr->query_player();
      usr->set_player( player );
      player->set_user( usr );
      player = tmp_player;
      player->set_user( this_object() );
      usr->quit();
      write_file( "/logs/logins", ctime( time() ) + "\t" + query_ip_number(this_object()) +
         "\t" + this_object()->query_name() +" reconnects\n" );
      player->set_linkdead( 0 );
      send_message( "Other copy kicked.\n" );
      USER_D->add_user( user_name, this_object() );
      player->write_prompt();
      remove_call_out( timeout_handle );
    }
  } else if( str == "n" ) {
    send_message( "So long then.\n" );
    remove_call_out( timeout_handle );
    player->destruct();
    destruct_object( this_object() );
  } else {
    send_message( "Please enter y or n : " );
    player->input_to_object( this_object(), "handle_reconnect" );
  }
}

string query_name( void ) {
  return(user_name);
}

string query_player_name( void ) {
  return( player->query_name() );
}

void input_name( string str ) {
  if( !str || str == "" ) {
    send_message( "Please enter your name : " );
    player->input_to_object( this_object(), "input_name" );
  } else {
    str = lowercase( str );
    user_name = str;
    if( BANISH_D->is_banished(user_name) ) {
      /* user_name is a banished name */
      write_file( "/logs/logins", ctime( time() ) + "\t" + query_ip_number(this_object()) +
         "\t" + query_name() + " <- banished name\n" );
      send_message( "\nThe name '"+user_name+"' is reserved and not available for use.\n" );
      destruct_object( player );
      destruct_object( this_object() );
    }
    if( file_exists( "/data/players/" + str + ".o" ) ) {
      /* Player file exists */

      player->set_name( user_name );
      player->set_proper_name( capitalize( user_name ) );
      player->restore_me();
      send_message( "Enter your password : " );
      send_message( 0 );
      player->input_to_object( this_object(), "input_old_passwd" );
    } else {
      player->set_name( user_name );
      player->set_proper_name( capitalize( user_name ) );
      if( SITEBAN_D->is_newbanned(query_ip_number(this_object())) ) {
         /* site is new character banned */
         write_file( "/logs/logins", ctime( time() ) + "\t" + query_ip_number(this_object()) +
            "\t" + query_name() + " <- Newbanned site\n" );
         send_message( "\nThis site is under development and not yet open to players.\n"+
            "Please email woodie@altern.org about future access from your site.\n" );
         destruct_object( player );
         destruct_object( this_object() );
      }
      send_message( "Ah. New player.\n" );
      send_message( "Is '" + user_name + "' correct (y/n)? : ");
      player->input_to_object( this_object(), "input_correct_name" );
    }
  }
}

void input_correct_name( string str ) {
  if( !str || str == "" ) {
    send_message( "Please enter 'y' or 'n' : " );
      send_message( "Is '" + user_name + "' correct (y/n)? : ");
    player->input_to_object( this_object(), "input_correct_name" );
  }

  if( lowercase( str ) == "y" || lowercase( str ) == "yes" ) {
    send_message( "Enter your password : " );
    send_message( 0 );
    player->input_to_object( this_object(), "input_new_passwd" );
  } else {
    send_message( "Enter your name : " );
    send_message( 1 );
    player->input_to_object( this_object(), "input_name" );
  }
}

void input_old_passwd( string str ) {
  if( !str || str == "" ) {
    send_message( "\nPlease enter your password : " );
    send_message( 0 );
    player->input_to_object( this_object(), "input_old_passwd" );
  }
  if( crypt( str, "gurba" ) == player->query_password() ) {
    /* Passwords match */
    login_user();
  } else {
    send_message( "\nPasswords don't match!\n" );
    destruct_object( player );
    destruct_object( this_object() );
  }
}

void input_new_passwd( string str ) {

  write_file( "/logs/new_players", ctime( time() ) + "\t" + query_ip_number(this_object()) +
      "\t" + query_name() + "\n" );

  if( !str || str == "" ) {
    send_message( "\nPlease enter your password : " );
    send_message( 0 );
    player->input_to_object( this_object(), "input_new_passwd" );
  } else {
    player->set_password( crypt(str, "gurba" ) );
    send_message( "\nEnter password again : " );
    send_message( 0 );
    player->input_to_object( this_object(), "input_check_passwd" );
  }
}

void input_check_passwd( string str ) {
  if( !str || str == "" ) {
    send_message( "\nPlease enter the password again : " );
    send_message( 0 );
    player->input_to_object( this_object(), "input_check_passwd" );
  } else {
    if( crypt( str, "gurba" ) == player->query_password() ) {
      send_message( "\nEnter your gender (male/female) : " );
      send_message( 1 );
      player->input_to_object( this_object(), "input_get_gender" );
     } else {
      send_message( "\nThe passwords don't match.\n" );
      send_message( "Enter your password : " );
      send_message( 0 );
      player->input_to_object( this_object(), "input_new_passwd" );
    }
  }
}

void input_get_gender( string str ) {

  if( !str || str == "" ) {
    send_message( "Please enter your gender (male/female) : " );
    player->input_to_object( this_object(), "input_get_gender" );
    return;
  }

  str = lowercase( str );
  if( str == "m" || str == "male" ) {
    player->set_gender( 1 );
  } else if( str == "f" || str == "female" ) {
    player->set_gender( 2 );
  } else {
    send_message( "Please use 'male' or 'female'.\n" );
    send_message( "Please enter your gender (male/female) : " );
    player->input_to_object( this_object(), "input_get_gender" );
    return;
  }
  send_message( "\nPlease enter your real name : " );
  player->input_to_object( this_object(), "input_get_real_name" );
}

void input_get_real_name( string str ) {
  player->set_real_name( str );

  send_message( "Please enter your email address : " );
  player->input_to_object( this_object(), "input_get_email" );
}

void write_races( void ) {
  int i;
  string line;
  string *races;

  send_message( "\n" );

  races = RACE_D->query_races();
  for( i = 0; i < sizeof( races ); i++ ) {
    line = races[i] + "              ";
    line = line[..10];
    line += " - " + RACE_D->query_race_short( races[i] ) + "\n";
    send_message( line );
  }
  send_message( "\n" );
}

void input_get_email( string str ) {

  player->set_email_address( str );
  
  write_races();
  send_message( "Choose one of the above races for your character : " );
  player->input_to_object( this_object(), "input_get_race" );
}

void input_get_race( string str ) {

  if( !str || str == "" ) {
    send_message( "Please choose one of the races : " );
    player->input_to_object( this_object(), "input_get_race" );
    return;
  }

  if( !RACE_D->is_race( lowercase(str) ) ) {
    send_message( "Please choose one of the races : " );
    player->input_to_object( this_object(), "input_get_race" );
    return;
  }

  player->set_race( lowercase(str) );

  player->save_me();
  login_user();
}

void set_player( object p ) {
  player = p;
}

object query_player( void ) {
  return( player );
}
