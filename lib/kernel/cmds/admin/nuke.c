/*
 *   Coded by: Satch
 *   File    : /kernel/cmds/admin/nuke.c
 *   Date    : 03.07.98
 *   
 */

#define SYNTAX  "Syntax: nuke [-rd ] <player>\n"

int main( string arg )
{
   string name;
   string flag, tmp, tmp2;
   int remove, delete;

   if( !SECURE_D->query_admin( this_player()->query_name() ))
   {
      write("Only admin are allowed to do that!\n");
      return 1;
   }

   if( !arg || arg == "" )
   {
      write( SYNTAX );
      return 1;
   }

   arg = lowercase( arg );

   /* Check input for flags */
   if( sscanf( arg, "-%s %s", flag, name ) == 2 )
   {
      if( sscanf(" "+flag+" ", "%sr%s", tmp, tmp2 ) ==2 )
         remove = 1;
      if( sscanf(" "+flag+" ", "%sd%s", tmp, tmp2 ) == 2 )
         delete = 1;
      }
   write( "delete: "+delete+"\n" );
   write( "remove: "+remove+"\n" );
}
