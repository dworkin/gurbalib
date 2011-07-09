/*
 *  ??.??.??  Fudge created
 *  03.08.98  Satch added 'reason' for shutdown.
 *
 */

#define S_LOG  "/logs/shutdowns"
string reason;

void usage() {
  write("Usage: shutdown [-h] [now|MINUTES] REASON\n");
  write("Shutdown the server now or MINUTES minutes later.\n");
  write("REASON is a message why the shutdown is needed.\n");
  write("Note: there is no way to stop a shutdown.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: warmboot\n");
}

void do_shutdown() {
   object *usrs;
   int i;

   usrs = USER_D->query_users();

   for( i=0; i < sizeof( usrs ); i++ ) {
      usrs[i]->query_player()->message( "Shutdown initiated by : " +
         this_player()->query_Name() + "\n");
      usrs[i]->query_player()->message( "Game driver tells you: " +
         "Shutting down immediately!\n");
      usrs[i]->query_player()->message( "  Reason : " + reason + "\n");
      usrs[i]->query_player()->save_me();
   }
   shutdown();
}

void countdown( int mins) {
   object *usrs;
   int i;

   usrs = USER_D->query_users();

   if( mins == 0 ) {
      do_shutdown();
   } else {
      for( i=0; i < sizeof( usrs ); i++ ) {
         usrs[i]->query_player()->message( "Shutdown initiated by : " +
            this_player()->query_Name() + "\n");
         usrs[i]->query_player()->message( "Game driver tells you: " +
            "Shutting down in " + mins + " minutes!\n");
         usrs[i]->query_player()->message( "  Reason : " + reason + "\n");
      }
      call_out( "countdown", 60, mins -1 );
   }
}

void main( string arg ) {
   object *usrs;
   string time;

   if( !arg || arg == "" ) {
      usage();
      return;
   }

   if (sscanf(arg, "-%s",arg)) {
     usage();
     return;
  }

   if( sscanf( arg, "%s %s", time, reason ) !=2 ) {
      usage();
      return;
   }

   if( !require_priv( "system" ) ) {
     write("You need admin permissions to do that.");
     return;
   }

   if( lowercase( time ) == "now" ) {
      write_file( S_LOG, ctime( time() ) + ": " + 
         this_player()->query_Name() + " forced a shutdown.\n" + "REASON: "
         + reason + "\n");
      do_shutdown();
   } else {
      write_file( S_LOG, ctime( time() ) + ": " + 
         this_player()->query_Name() + " forced a shutdown.\n" + "REASON: " +
         reason + "\n" );
       countdown( str2val( time ));
   }
}

