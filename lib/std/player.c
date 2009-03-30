/* Player object. By Fudge */

#include <channel.h> 
#include <type.h>
#include <limits.h>

inherit obj OBJECT;
inherit con CONTAINER;
inherit bod BODY;
inherit M_MESSAGES;
inherit "/std/editor";
inherit "/std/modules/m_autoload_string";
inherit "/std/modules/m_language";

static object user;		/* This players user object */
static string input_to_func;	/* The function we're redirecting input to */
static object input_to_obj;	/* The object we're redirecting input to */
static object possessing;	/* The object this player is possessing */
static int linkdead;		/* Are we linkdead? */
static int quitting;		/* Are we in the process of quitting? */
static int timestamp;		/* Last time we got input */
static int more_line_num;	/* How far in the file we're more'ing are we */
static string *more_lines;	/* All the lines in the file we're more'ing */
string last_tell;               /* Who did we get a tell from last? */
static mapping item_commands;	/* Commands that are local to worn/wielded items. */

string real_name;		/* This players real name */
string email_address;		/* The email address */
mapping board_read;		/* Status of messages read */
mapping environment_variables;	/* The environment variables of the player */
string title;			/* The title */
string player_name;		/* The player name */
string password;		/* The password */
string *cmd_path;		/* The path which is searched for comands */
string *channels;		/* Channels we're listening to */
string *ignored;        /* the users we are ignoring */
mapping alias;			/* The players aliases */
int last_login;			/* The last login */
mapping guilds;			/* The guilds the player is a member of. The values are the guild title. */
mapping custom_colors;          /* custom color symbols for this player */

void save_me( void );
void restore_me( void );
void set_env( string name, mixed value );
mixed query_env( string name );
string query_title( void );

void create( void ) {
  obj::create();
  con::create();
  bod::create();

  board_read = ([ ]);
  channels = ({ "gossip", "announce" });
  ignored = ({ });
  title = "$N the nondescript";
  long_desc = "";
  set_brief( "A nondescript player" );
  timestamp = time();
  set_env( "cwd", "/" );
  set_env( "pwd", "/" );
  set_env( "width", "78" );
  set_env( "height", "23" );

  custom_colors = ([ ]);
  item_commands = ([ ]);
}

/* Save the player */
void save_me( void ) {
  save_object( "/data/players/"+player_name+".o" );
}

/* Restore the player */
void restore_me( void ) {
  if( !restore_object( "/data/players/"+player_name+".o" ) ) {
    write( "Error while restoring \"/data/players/" + player_name+".o" );
    write( "Please notify the administration.");
    return;
  }
  if( !board_read )
    board_read = ([ ]);
  set_id( player_name );
  if( !alias )
    alias = ([ ]);
}

/* Login the player */
void login_player( void ) {
  int i;
  string *didlog;
  
  /* If we're a wiz, show the didlog since last login */
  if( SECURE_D->query_priv( player_name ) > 0 ) {
    didlog = DID_D->get_entries( last_login );

    if( didlog ) { 
      for( i = 0; i < sizeof( didlog ); i++ ) {
   if( didlog[i] == "" )
     write( "\n" );
   else
     write( didlog[i] );
      } 
    }
  }
  if( !last_login ) {
    /* A new player */
    EVENT_D->event( "new_player", player_name );
    last_login = time();
  } else {
    last_login = time();
    /* Call the login event */
    EVENT_D->event( "player_login", player_name );
  }

  /* Gender less? Set the player to male */
  if( !query_gender() )
    set_gender( 1 );

  /* Set the proper name */
  if( !query_proper_name() ) {
    set_proper_name( capitalize( player_name ) );
  }

  /* Set the current working directory */
  if( !query_env( "cwd" ) )
    set_env( "cwd", "/" );

  /* Subscribe to default channels */
  if( !channels ) {
    channels = ({ "gossip", "announce" });
  }

  /* Register with the subscribed channels */
  for( i = 0; i < sizeof( channels ); i++ ) {
    if( CHANNEL_D->query_channel( channels[i] ) ) {
      CHANNEL_D->chan_join( channels[i], this_player() );
    } else {
      channels[i] = nil;
    }
  }
  initialize_race();    /* Load up this players race */
  set_brief( query_title() ); /* Set the brief description */
  set_hit_skill( "combat/unarmed" );
  ANSI_D->set_player_translations( custom_colors );
}

int query_last_login( void ) {
  return( last_login );
}

void set_last_tell( string who ) {
  last_tell = who;
}

string query_last_tell( void ) {
  return( last_tell );
}

int is_living( void ) {
  return 1;
}

int is_player( void ) {
  return 1;
}

int is_possessing( void ) {
  if( possessing )
    return 1;
  return 0;
}

object query_possessing( void ) {
  return( possessing );
}

void set_possessing( object ob ) {
  possessing = ob;
}

void set_env( string name, mixed value ) {
  if( !environment_variables ) {
    environment_variables = ([ ]);
  }
  environment_variables[name] = value;
  if(player_name)
  save_me();
}

mixed query_env( string name ) {
  if( !environment_variables ) {
    environment_variables = ([ ]);
  }
  return( environment_variables[name] );
}

string *query_env_indices( void ) {
  if( !environment_variables ) {
    environment_variables = ([ ]);
  }
  return( map_indices( environment_variables ) );
}

int query_ansi( void ) {
  mixed x;

  x = query_env( "ansi");
  if( typeof( x ) == T_NIL )
    return 1; /* ansi is on if query_env("ansi") is undefined */
  return x;
}

void set_ansi( int state ) {
  set_env( "ansi", state );
  save_me();
}

int query_board_read( string board ) {
  if(!board_read[board])
    return 0;
  return( board_read[ board ] );
}

void set_board_read( string board, int num ) {
  board_read[ board ] = num;
  save_me();
}

void set_user( object usr ) {
  user = usr;
}

void set_title( string t ) {
  title = t;
  set_brief( query_title() );
}

string query_title( void ) {
  string t;

  t = title;
  if( ! player_name ) {
    return "";
  }

  if( !t || t == "" )
    t = "$N the title less";
  return( replace_string( t, "$N", capitalize( player_name ) ) );
}

string query_title_string( void ) {
  return( title );
}

void set_linkdead( int flag ) {
  if( flag == 1 ) {
    set_brief( query_title() + " [link-dead]" );
    linkdead = call_out( "do_quit", LINKDEAD_TIMEOUT, nil );
  } else {
    set_brief( query_title() );
    if( linkdead )
      remove_call_out( linkdead );
    linkdead = 0;
  }
}

void set_editing( int flag ) {
  if( flag == 1 )
    set_brief( query_title() + " [editing]" );
  else 
    set_brief( query_title() );
}

int query_linkdead( void ) {
  return( linkdead > 0 );
}

int query_idle( void ) {
  return( time() - timestamp );
}

object query_user( void ) {
  return(user);
}

void set_name( string name ) {
  player_name = name;
  set_id( name );
}

string query_name( void ) {
	return player_name;
}

string query_Name( void )
{
	return capitalize( player_name );
}
void set_password( string passwd ) {
  password = passwd;
}

string query_password( void ) {
  return password;
}

void set_real_name( string str ) {
	real_name = str;
}

string query_real_name( void ) {
	return( real_name );
}

void set_email_address( string str ) {
	email_address = str;
}

string query_email_address( void ) {
	return( email_address );
}

void initialize_cmd_path( void ) {
	cmd_path = ({ "/cmds/player" });
}

/* Add a path to the command path */
void add_cmd_path( string path ) { 
	cmd_path -= ({ path });
	cmd_path += ({ path });
}

string *query_path( void ) {
	return cmd_path;
}

void add_channel( string chan ) {
	if( !channels )
		channels = ({ });
	channels -= ({ chan });
	channels += ({ chan });
}

void remove_channel( string chan ) {
	if( !channels )
		channels = ({ });
	channels -= ({ chan });
}

string *query_channels( void ) {
  return( channels );
}

void add_ignore( string who ) {
    if (who == "") return;
/*    if ( !ignored ) ignored = ({ });*/
    ignored += ({ lowercase(who) });
}

void remove_ignore( string who ) {
    if ( !ignored ) ignored = ({ });
    ignored -= ({ lowercase(who) });
}

int query_ignored( string who ) {
    if ( !ignored ) ignored = ({ });    
    who = lowercase(who);
    return member_array( who, ignored ) >= 0;
}

string *query_ignored_all() {
    if ( !ignored ) ignored = ({ });
    return ignored;
}


/* Redirect input to another funtion */
void input_to( string func ) {
  input_to_obj = this_player();
  input_to_func = func;
}

/* Redirect input to another object */
void input_to_object( object ob, string func ) {
  input_to_obj = ob;
  input_to_func = func;
}

/* Send a message to the player */
void message( string str ) {
  if( this_object()->is_snooped() )
    this_object()->do_snoop( str );
  this_object()->query_user()->wrap_message( str );
}

/* Send an almost unmodified message to the player */
void message_orig( string str ) {
  if( this_player()->is_snooped() )
    this_player()->do_snoop( str );
  query_user()->put_message( str );
}

void write_prompt() {
  string prompt;

  if( this_player()->is_editing() ) {
    out( "%^GREEN%^edit> %^RESET%^" );
    return;
  }

  prompt = query_env( "prompt" );
  if( !prompt ) {
    prompt = "> ";
  } else {
    prompt = replace_string( prompt, "%t", ctime(time())[11..18] );
    prompt = replace_string( prompt, "%n", capitalize( player_name ) );
    prompt = replace_string( prompt, "%m", MUD_NAME );
    prompt = replace_string( prompt, "%w", query_env( "cwd" ) );
    prompt = replace_string( prompt, "%_", "\n" );
    prompt = replace_string( prompt, "%l", this_environment()->file_name() );
    if( !this_environment()->query_area() ) {
      prompt = replace_string( prompt, "%a", "(none)" );
    } else {
      prompt = replace_string( prompt, "%a", this_environment()->query_area() );
    }
    prompt = replace_string( prompt, "%h", "" + query_stat( "hp" ) );
    prompt = replace_string( prompt, "%H", "" + query_stat( "max_hp" ) );
  }

  out( prompt + "%^RESET%^ " );
}

/* More a set of lines */
void more( string *lines ) {
  string msg;
  mixed height;

  height = query_env( "height" );
  if( height == nil )
    height = 23;
  else if(stringp(height)) 
    height = str2val(height);

  if(height == -1) height = 23;
  if(height == 0) height = INT_MAX;

  more_line_num = 0;
  more_lines = lines;

  if( sizeof( lines ) > height + more_line_num ) {
    out_unmod( implode( lines[more_line_num..more_line_num+height], "\n" ) );
    out( "\n%^BOLD%^--More--(" + ((more_line_num+height)*100)/sizeof( lines ) + "%)%^RESET%^" );
    more_line_num += height + 1;
    input_to( "more_prompt" );
  } else {
    msg = implode( lines[more_line_num..], "\n" );
    out_unmod( msg + "\n" );
  }
}

/* Write out the more prompt after each page */
void more_prompt( string arg ) {
  string msg;
  mixed height;

  if( !arg || arg == "" )
    arg = " ";
  switch( arg[0] ) {
  case 'q':
  case 'Q':
    write_prompt();
    return;
    break;
  }

  height = query_env( "height" );

  if(height == nil) height = 23;
  else if(stringp(height)) height = str2val(height);

  if(height == -1) height = 23;
  else if(height == 0) height = INT_MAX;

  if( sizeof( more_lines ) > height + more_line_num ) {
    out_unmod( implode( more_lines[more_line_num..more_line_num+height], "\n" ) );
    out( "\n%^BOLD%^--More--(" + ((more_line_num+height)*100)/sizeof( more_lines ) + "%)%^RESET%^" );
    more_line_num += height + 1;
    input_to( "more_prompt" );
  } else {
    msg = implode( more_lines[more_line_num..], "\n" );
    out_unmod( msg + "\n" );
    write_prompt();
  }
}

/* Look around */
void do_look( int brief ) {
  this_environment()->event( "body_look", this_player() );
  write( " " );
  if( query_env( "show_location" ) ) 
    write( "%^BOLD%^" + query_environment()->file_name() + "%^RESET%^" );
  write( this_environment()->query_desc(0) );
}

/* Move */
void do_go( string dir ) {
  string error;

  error = this_environment()->body_exit( this_player(), dir );

  if( error )
    write( error );
}

/* Quit */
void do_quit( string str ) {
  object *objs;
  int i;

  this_object()->compose_autoload_string();
  
  objs = query_inventory() + ({ });

  if( is_possessing() )
    call_other( "/cmds/wiz/possess", "main", "" );

  for( i=0; i < sizeof( objs ); i++ ) { 
    if( objs[i]->is_undroppable() ) {
      objs[i]->destruct();
    }
    else if( objs[i]->move( this_object()->query_environment() ) ) {
      this_object()->targetted_action( "$N $vdrop $o.", nil, objs[i] );
    }
    else {
      objs[i]->destruct();
    }
  }

  this_object()->simple_action( "$N $vquit." );
  for( i = 0; i < sizeof( channels ); i++ ) {
    if( CHANNEL_D->query_channel( channels[i] ) ) {
      CHANNEL_D->chan_leave( channels[i], this_object() );
    } else {
      channels[i] = nil;
    }
  } 
  EVENT_D->event( "player_logout", player_name );
  quitting = 1;
  query_user()->quit();
}

/* Destruct this player */
void destruct( void ) {
  move_or_destruct_inventory();
  ::destruct();
}

/* Alias handling */

int is_alias( string cmd ) {
  if( !alias )
    alias = ([ ]);
  if( alias[cmd] )
    return( 1 );
  return( 0 );
}

string query_alias( string cmd ) {
  if( !alias )
    alias = ([ ]);
  return( alias[cmd] );
}

void add_alias( string cmd, string new_alias ) {
  if( !alias )
    alias = ([ ]);
  alias[cmd] = new_alias;
}

void remove_alias( string cmd ) {
  if( !alias )
    alias  = ([ ]);

  alias[cmd] = nil;
}

mapping query_aliases( void ) {
  if( !alias )
    alias = ([ ]);
  return( alias );
}

/* Add to the item command mapping */
void add_item_command( string command, object ob ) {
  if( !item_commands )
    item_commands = ([ ]);
  item_commands[command] = ob;
}

void remove_item_command( string command ) {
  if( !item_commands )
    item_commands = ([ ]);
  item_commands[command] = nil;
}

/* Guild routines */

void join_guild( string guild ) {
  if( !guilds )
    guilds = ([ ]);
  guilds[guild] = GUILD_D->query_guild_title( guild );
  cmd_path += ({ "/cmds/guild/" + guild });
  save_me();
}

void leave_guild( string guild ) {
  if( !guilds )
    guilds = ([ ]);
  guilds[guild] = nil;
  cmd_path -= ({ "/cmds/guild/" + guild });
  set_title( "$N the guildless" );
  save_me();
}

int guild_member( string guild ) {
  if( !guilds )
    guilds = ([ ]);
  if( guilds[guild] )
    return( 1 );
  return( 0 );
}

string *query_guilds( void ) {
  return( map_indices( guilds ) );
}

/* Process input from the player */
void receive_message( string message ) {
  
   mixed   result;
   string  func;
   string  cmd;
   string  arg;
   string *exits;
   int i;
   int flag;
   
   flag = 0;
   
   /* Update the timestamp so we're not idle */
   timestamp = time();
   
   arg = "";
   
   if( this_player()->is_snooped() )
      this_player()->do_snoop( message );
   
   /* Redirect the input somewhere else */
   if( input_to_func != "" ) {
      func = input_to_func;
      input_to_func = "";
      call_other( input_to_obj, func, message );
      /* Are we editing? */
   } else if( is_editing() ) {
      this_player()->edit( message );
   } else {
     string temp;
      /* Expand the command */
      temp = ALIAS_D->expand_alias( message );
      if(temp) message = temp;
      /* Split the input into command and argument */
      if( sscanf( message, "%s %s", cmd, arg ) != 2 ) 
	 cmd = message;
      
      if( is_alias( cmd ) ) {
	 message = ALIAS_D->do_expand( query_alias( cmd ), arg );
	 if( sscanf( message, "%s %s", cmd, arg ) != 2 ) 
	    cmd = message;
      }
      
      if( cmd != "" ) {
	 if( cmd[0] == '\'' ) {
	    if( arg == "" ) {
	       arg = cmd[1..];
	    } else {
	       arg = cmd[1..] + " " + arg;
	    }
	    cmd = "say";
	 } else if( cmd[0] == ';' ) {
	    if( arg == "" ) {
	       arg = cmd[1..];
	    } else {
	       arg = cmd[1..] + " " + arg;
	    }
	    cmd = "emote";
	 }
      }
      
      /* Substitute 'me' with my name */
      if( arg == "me" )
	 arg = this_player()->query_id();
      
      /* Check for a command, and call the command if it's found */
      if( !flag ) {
	 for( i = 0; i < sizeof( cmd_path ); i++ ) {
	    if( file_exists( cmd_path[i] + "/" + cmd + ".c" ) ) {
	       call_other( cmd_path[i] + "/" + cmd, "main", arg );
	       flag = 1;
	       break;
	    }
	 }
      }
      
      /* Check for a verb */
      if( !flag ) {
	 result = PARSE_D->parse( cmd + " " + arg );
	 if( result ) {
	    if( typeof( result ) == T_STRING ) {
	       write( result );
	    }
	    flag = 1;
	 }
      }

      if( !flag ) {
	 /* Check for an item command */
	 int i;
	 string *item_cmds;
	 
	 item_cmds = map_indices( item_commands );
	 for( i = 0; i < sizeof( item_cmds ); i++ ) {
	    if( item_cmds[i] == cmd ) {
	       call_other( item_commands[ item_cmds[i] ], "do_" + cmd, arg );
	       flag = 1;
	    }
	 }
      }

      if ( !flag ) {
         /* Check for a room command */
         string roomcmd_h;
         roomcmd_h = this_environment()->query_room_command(cmd);
         if (roomcmd_h) {
           call_other( this_environment(), roomcmd_h, arg );
           flag = 1;
         }
      }
      
      if( !flag ) {
	 /* Check if the command is an emote */
	 if( EMOTE_D->is_emote( cmd ) ) {
	    string *rules;
	    string rule;
	    object target;
	    
	    rules = EMOTE_D->query_rules( cmd );
	    
				/* Targetted emote? Find the target */
	    if( arg != "" ) {
	       target = this_environment()->present( arg );
	    } else {
	       target = nil;
	    }
	    if( target ) {
	       /* We've found our target, check for the correct rule */
	       if( target->is_living() ) {
		  /* We're looking for a LIV rule */
		  if( member_array( "LIV", rules ) != -1 ) {
		     rule = "LIV";
		  } else {
		     rule = "";
		  }
	       } else {
		  /* We're looking for a OBJ rule */
		  if( member_array( "OBJ", rules ) != -1 ) {
		     rule = "OBJ";
		  } else {
		     rule = "";
		  }
	       }
	    } else {
	       /* Or are we just looking for a string? */
	       if( member_array( "STR", rules ) != -1  && arg != "" ) {
		  rule = "STR";
	       } else {
		  rule = "";
	       }
	    }
	    
	    if( rule == "LIV" ) {
	       targetted_action( EMOTE_D->query_emote( cmd, rule ), target );
	    } else if( rule == "OBJ" ) {
	       simple_action( EMOTE_D->query_emote( cmd, rule), target );
	    } else if( rule == "STR" ) {
	       simple_action( EMOTE_D->query_emote( cmd, rule), arg );
	    } else  {
	       if( member_array( "", rules ) != -1 )
		  simple_action( EMOTE_D->query_emote( cmd, rule) );
	       else
		  write( "No such emote.\n" );
	    }
	    flag = 1;
			}
      }
      
      if( !flag ) {
	 /* Is it a channel? */
	 if( CHANNEL_D->query_channel( cmd ) == 1 ) {
				/* Okey, it's a channel. Are we priveleged enough to use it? */
	    if( CHANNEL_D->query_priv( cmd )+1 == READ_ONLY ||
		CHANNEL_D->query_priv( cmd ) <= SECURE_D->query_priv( player_name ) ) { 
	       
	       flag = 1;
            "/cmds/player/chan"->chan_cmd( cmd, arg );
	    }
	 }
      }
      
      if( !flag ) {
	 /* Is it an exit? */
	 exits = this_environment()->query_exit_indices();
	 for( i = 0; i < sizeof( exits ); i++ ) {
	    if( exits[i] == lowercase( cmd ) ) {
	       call_other( "/cmds/player/go", "main", cmd );
	       flag = 1;
	    }
			}
      }
      
      if( !flag && cmd != "" ) {
	 write( "What?\n" );
      }
      if( !quitting && input_to_func == "" && !is_editing() ) 
			write_prompt();
   }
}

void set_custom_color( string name, string * symbols ) {
  int i, sz;
  string tmp;

  tmp = "";
  if(!custom_colors) custom_colors = ([ ]);

  if(!symbols) {
    custom_colors[name] = nil;
    write("Removed color symbol "+name+"\n");
  } else {
    for( i=0, sz = sizeof( symbols); i < sz; i++ ) {
      if( strstr( "%^", symbols[i] ) == -1 ) {
        symbols[i] = uppercase( symbols[i] );
        if( !ANSI_D->query_any_symbol( symbols[i] ) ) {
          /* Each symbol must resolve to a pre-defined token */
          write( "Symbolic color tokens must be composed of only valid base color tokens "+
               "or pre-existing custom tokens.\n" +
               "see 'ansi show' for valid tokens" );
          return;
        } else {
          switch(ANSI_D->check_recursion(name, symbols[i])) {
            case 2 : write("Loop in symbolic tag "+name+" : "+symbols[i]);
                     return;
            case 1 : write("Too many levels of symbolic tags for "+name);
                     return;
          }
        }
        tmp += "%^" + symbols[i] + "%^";
      } else {
        write( "Symbolic color tokens cannot (YET) contain custom tokens\n" );
        return;
      }
    }
 
    custom_colors[name] = tmp;
    out_unmod( name + " is now " + tmp + "\n" );
  }

  ANSI_D->set_player_translations(custom_colors);
  save_me();
}
