/*Made by Aphex on Fri 21 Nov 97*/
/* Fixed to handle goto'ing of room files by Fudge. */
/* Fixed to properly setup rooms that get loaded by this command */

void usage() {
  write("Usage: goto [-h] PLAYER|ROOM\n");
  write("Find PLAYER, and then transport you to them.\n");
  write("or goto the specified ROOM.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: home, summon, where\n");
}

void main( string str ) {
  object usr;
  object player;

  if (!str || str == "") {
     usage();
     return;
  }
  if (sscanf(str, "-%s",str)) {
    usage();
    return;
  }
  
  usr = USER_D->find_user(str);
  if (usr){
    if (this_player()->query_environment() != 
      usr->query_player()->query_environment()){  
      this_player()->query_environment()->tell_room( this_player(), 
        capitalize(this_player()->query_name()) + " disappears.\n");
      player = usr->query_player();
      this_player()->move(player->query_environment()->base_name());
      this_player()->query_environment()->tell_room( this_player(), 
        capitalize(this_player()->query_name()) + " appears from nowhere.\n");
      this_player()->do_look(0);
    } else { 
      out( "Going somewhere?\n");
    }
  } else {
    string file;
    object ob;
    file = normalize_path(str, this_player()->query_env( "cwd" ));
    if ( file_exists( file + ".c")) {
       file = file + ".c";
    } 
    if( file_exists( file) ) {
      if(!(ob = find_object( file ) ) ) {
        catch {
          ob = compile_object( file );
          ob->setup();
          ob->setup_mudlib();
        } : {
          write("Could not load "+str);
        }
      }
      if (ob == this_environment()) {
         write("You are already there.\n");
         return;
      }

      this_environment()->event( "body_leave", this_player() );
      this_environment()->tell_room( this_player(), 
        capitalize(this_player()->query_name()) + " disappears.\n" );
      if( !ob || !this_player()->move( ob ) ) {
	write( "\nConstruction blocks your path.\n" );
      } else {
         this_player()->do_look( 0 );
      }
      this_environment()->event( "body_enter", this_player() );
      this_environment()->tell_room( this_player(), 
         capitalize(this_player()->query_name()) + " appears.\n" );
    } else {
      write( "Unable to find " + str + ".\n" );
    }
  }
}
