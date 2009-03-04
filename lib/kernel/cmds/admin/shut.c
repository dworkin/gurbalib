/*
 *  ??.??.??  Fudge created
 *  03.08.98  Satch added 'reason' for shutdown.
 *
 */

#define MSG1   "Game driver tells you: Shutting down immediatly!\n"
#define MSG2   "Game driver tells you: Shutting down in "+mins+" minutes!\n"
#define SYNTAX "Useage: shutdown <\"now\"/minutes> <reason>\n"
#define S_LOG  "/logs/shutdowns"

void    do_shutdown();
void    countdown( int mins );


void main( string arg )
{
   object *usrs;
   string time, reason;

   if( arg == "" )
   {
      write(SYNTAX);
      return;
   }

   if( sscanf( arg, "%s %s", time, reason ) !=2 )
   {
      write( SYNTAX );
      return;
   }

   if( lowercase( time ) == "now" )
   {
   write_file( S_LOG, 
      ctime( time() )+": "+this_player()->query_Name()+" forced a shutdown.\n"+
      "REASON: "+reason+"\n" );

      do_shutdown();

   } else {

   write_file( S_LOG,
      ctime( time() )+": "+this_player()->query_Name()+" forced a shutdown.\n"+
      "REASON: "+reason+"\n" );

       countdown( str2val( time ));
   }
}

void do_shutdown()
{
   object *usrs;
   int i;

   usrs = USER_D->query_users();

   for( i=0; i < sizeof( usrs ); i++ )
   {
      usrs[i]->query_player()->message( MSG1 );
      usrs[i]->query_player()->save_me();
   }
   shutdown();
}

void countdown( int mins )
{
   object *usrs;
   int i;

   usrs = USER_D->query_users();

   if( mins == 0 )
   {
      do_shutdown();
   
   } else {
   
   for( i=0; i < sizeof( usrs ); i++ )
   {
      usrs[i]->query_player()->message( MSG2 );
   }
   call_out( "countdown", 60, mins -1 );
   }
}