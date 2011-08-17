void usage () {
   if( query_wizard( this_player() ) ) {
      write("Usage: score [-h] [-q] [PLAYER]\n");
      write("Gives you basic stats about player PLAYER.\n");
      write("If no player is given give your stats.\n");
      write("Options:\n");
      write("\t-h\tHelp, this usage message.\n");
   } else {
      write("Usage: score [-h]\n");
      write("Gives you basic stats about your character.\n");
      write("Options:\n");
      write("\t-h\tHelp, this usage message.\n");
      write("\t-q\tAlso display quests you have completed.\n");
   }
}

void main( string str ) {
   int max_hp, hp, expr, level, quest;
   int ac, i, ducats, royals, crowns;
   mixed *money;
   object obj;

   quest = 0;
   if (str == "-q") {
      str = "";
      quest = 1;
   } else if (sscanf(str, "-q %s",str)) {
      quest = 1;
   } else if (sscanf(str, "-%s",str)) {
     usage();
     return;
   }

   if (str && str != "") {
      if (query_wizard( this_player())) {
         obj = USER_D->find_player(str);
         if (!obj) {
            write("Unable to find player: " + str + "\n");
            return;
         }
      } else {
         usage();
         return;
      }
   } else {
      obj = this_player();
   }
   
   money = obj->query_all_coins();
   max_hp = obj->query_max_hp();
   hp     = obj->query_hp();
   expr   = obj->query_expr();
   ac     = obj->query_defense();
   level  = obj->query_level();

   write( "[ " + obj->query_name() + " ] " + obj->query_title() + "\n" );
   write( "Strength    :  " + obj->query_stat("str") +
	"\t\t" + "Hit points  :   " + hp + "/" + max_hp + "\n" );
   write( "Intelligence:  " + obj->query_stat("int") +
	"\t\t" + "Experience  :   " + expr + "\n" );
   write( "Wisdom      :  " + obj->query_stat("wis") +
	"\t\t" + "Level       :   " + level + "\n" );
   write( "Dexterity   :  " + obj->query_stat("dex") +
	"\t\t" + "Armor class :   " + ac + "\n" );
   write("Constitution:  " + obj->query_stat("con") );
   write("Charisma    :  " + obj->query_stat("cha") +
        "\t\t" + "Money:\n" );

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
   write("\t\t\t\t\tDucats: " + ducats ); 
   write("\t\t\t\t\tRoyals: " + royals ); 
   write("\t\t\t\t\tCrowns: " + crowns ); 

   if (quest) {
      string *quests;
      int j,k;

      write("Quests Completed:\n");
      quests=this_player()->query_quests_completed();
      if (quests) {
         k=sizeof(quests);
         for(j=0;j<k;j++) {
            write("\t" + quests[j] + "\n");
         }
      }
   }
   
   return;
}

