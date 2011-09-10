void usage() {
  write("Usage: stats [-h] [object]\n");
  write("Display the stat's for the specified object/person.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: add_base, add_bonus, score\n");
}

void main( string arg ) {
   int i,j;
   int stat, max_stat;
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
      stat_abrvs = ({ "str", "dex", "con", "int", "wis", "cha" });

      stat_names = ({"strength    ", "dexterity   ", "constitution",
                     "intelligence", "wisdom      ", "charisma    ", });
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
      stat = ob->query_hp();
      max_stat = ob->query_max_hp();
      write("\n\t"+"Hitpoints    :  " + stat + "/" + max_stat + "\n");
      stat = ob->query_mana();
      max_stat = ob->query_max_mana();
      write("\t"+"Mana         :  " + stat + "/" + max_stat + "\n");
      stat = ob->query_end();
      max_stat = ob->query_max_end();
      write("\t"+"Endourance   :  " + stat + "/" + max_stat + "\n");
   }
}   
