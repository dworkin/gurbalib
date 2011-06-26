void usage () {
   write("Usage: score [-h]\n");
   write("Gives you basic stats about your character.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
   int max_hp, hp;
   int expr;
   int ac, i, ducats, royals, crowns;
   mixed *money;

   if (str && str != "") {
      usage();
      return;
   }
   
   money = this_player()->query_all_coins();
   max_hp = this_player()->query_max_hp();
   hp     = this_player()->query_hp();
   expr   = this_player()->query_expr();
   ac     = this_player()->query_defense();



   write( "[ "+this_player()->query_name() + " ]" + "\n" );
   write( "Strength    :  " + this_player()->query_stat("str") +
	"\t\t" + "Hit points  :   " + hp + "/" + max_hp + "\n" );
   write( "Intelligence:  " + this_player()->query_stat("int") +
	"\t\t" + "Experience  :   " + expr + "\n" );
   write( "Wisdom      :  " + this_player()->query_stat("wis") +
	"\t\t" + "Armor class :   " + ac + "\n" );
   if( sizeof( money ) == 0 ) {
        write("Dexterity   :  " + this_player()->query_stat("dex")  +
		"\t\tYou are broke.\n");
	write("Constitution:  " + this_player()->query_stat("con") );
        write("Charisma    :  " + this_player()->query_stat("cha") );

   } else {
      for( i = 0; i < sizeof( money ); i++ ) {
         switch( money[i][0] ) {
            case "ducat" : ducats = money[i][1];
               break;
            case "royal" : royals = money[i][1];
               break;
            case "crown" : crowns = money[i][1];
               break;
            default:
               break;
         }
      }
      write("Dexterity   : " + this_player()->query_stat("dex")  +
      	 "\t\tDucats: " + ducats ); 
      write("Constitution: " + this_player()->query_stat("con") +
         "\t\tRoyals: " + royals ); 
      write("Charisma    : " + this_player()->query_stat("cha") +
         "\t\tCrowns: " + crowns ); 
   }
   
   return;
}
