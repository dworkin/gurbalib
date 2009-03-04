int main( string str )
{
   int max_hp;
   int hp;
   int expr;
   int ac;

   max_hp = this_player()->query_max_hp();
   hp     = this_player()->query_hp();
   expr   = this_player()->query_expr();
   ac     = this_player()->query_defense();

   write( "[ "+this_player()->query_name() + " ]" + "\n\n" );
   write( "\t" + "hit points  :   " + hp + "/" + max_hp + "\n" );
   write( "\t" + "experience  :   " + expr + "\n" );
   write( "\t" + "armor class :   " + ac + "\n" );
   
   return 1;
}
