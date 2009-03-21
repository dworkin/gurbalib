/*
 * This function is atomic so that the destruct_object() gets
 * undone if the following compile_object() fails.
 *
 */
static atomic object recompile_library(string str) {
  object ob;

  ob = find_object(str);
  if(ob) {
    if(ob->num_clones()) {
      error ("Cannot recompile object that is inherited and has clones");
    } else {
      destruct_object(ob);
      return compile_object(str);
    }
  }
}

void main( string str ) {
  string path;
  object *objs;
  object *players;
  object ob;
  object old_room;
  int i;


  if( !str || str == "" ) {
    str = this_player()->query_env( "cwf" );
  }

  if( !str || str == "" ) {
    write( "You need to specify a filename." );
    return;
  }

  path = this_player()->query_env( "cwd" );

  if( strlen(str) > 2 ) {
    if( str[strlen(str)-2] == '.' 
	&& str[strlen(str)-1] == 'c' )
      str = str[..strlen(str)-3];
  }

  path = normalize_path( str, path );
  if( !path || path == "" ) {
    write( "Access denied.\n" );
    return;
  }

  if( str == "here" ) {
    str = this_environment()->base_name();

    /* Check for errors before moving people out of the room */

    this_player()->write( str + "\n" ); 

    ob = compile_object( str );

    if( ob ) {
      /* It compiled fine. Move'em. */
      objs = this_environment()->query_inventory();
      players = ({ });
      for( i = 0; i < sizeof( objs ); i++ ) {
	if( objs[i]->is_player() )
	  players += ({ objs[i] });
      }
      
      old_room = this_environment();
      
      for( i = 0; i < sizeof( players ); i++ ) {
	players[i]->move( "/domains/gurba/void" );
      }
      
      old_room->destruct();

      /* And move into the new room */

      call_other( str, "???" );

      for( i = 0; i < sizeof( players ); i++ ) {
	players[i]->move( str );
      }
      this_player()->do_look( 0 );
    }
  } else if( file_exists( path + ".c" ) ) {
    this_player()->set_env( "cwf", path );
    catch {
      ob = compile_object( path );
    } : {
      switch(caught_error()) {
        case "Cannot recompile inherited object" :
          write( path + " is inherited, trying to destruct/compile." );
          ob = recompile_library(path);
          break;
        default :
          rethrow();
          break;
      }
    }
    if( ob ) {
      write( "Compilation successful.\n" );
    }
  } else {
    write( "File not found.\n" );
  }
}
