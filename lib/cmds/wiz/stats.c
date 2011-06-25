void usage() {
  write("Usage: stats [-h] [object]\n");
  write("Display the stat's for the specified object/person.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string arg ) {
   int i,j;
   int hp, max_hp;
   string *stat_abrvs;
   string *stat_names;
   object ob;

   if (sscanf(arg, "-%s",arg)) {
      usage();
      return;
   }

   if(arg != "") {
      ob = this_player()->query_environment()->present( arg );
      if( !ob ) {
         write(arg+" is not here!\n");
         ob = nil;
      } else {
            write(object_name(ob) + "(" + ob->query_name() + "):");
      }
   }
   else {
      ob = this_player();
   }

   if(ob) {
      hp = ob->query_hp();
      max_hp = ob->query_max_hp();
      stat_abrvs = ({ "str", "con", "end", "dex", "agl", "aim", 
                     "int", "wis", "per", "cha", "luc", "spr", "god" });

      stat_names = ({"strength    ", "constitution", "endurance   ",
                     "dexterity   ", "agility     ", "aim         ",
                     "intelligence", "wisdom      ", "perception  ",
                     "charisma    ", "luck        ", "spirituality",
                     "god bonus   " });
   
      j = 0;
   
      write("                        stat   base   bonus \n");
      write("-----------------------------------------------\n");
      for( i=0; i < sizeof( stat_names ); i++ ) {
         write("\t"+capitalize(stat_names[i])+" :   "
               +ob->query_stat(stat_abrvs[i])
               +"\t"
               +ob->query_base_stat(stat_abrvs[i])
               +"\t"
               +ob->query_bonus_stat(stat_abrvs[i])
               +"\n");
         ++j;
         if( j==3 ) {
            write("\n");
            j = 0;
         }

      }
      write("\n\n\t"+"Hitpoints    :  "+hp+"/"+max_hp+"\n");
   }
}   
