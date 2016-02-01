inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: stats [-h] [object]" });
   lines += ({ " " });
   lines += ({ "Display the stat's for the specified object/person." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tstats rat" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "score");

   add_also("wiz", "add_base");
   add_also("wiz", "add_bonus");
}

static void main(string arg) {
   int i, j, stat, max_stat, sz;
   string *stat_abrvs, *stat_names;
   object ob;

   if (!alsos) {
      setup_alsos();
   }

   if (sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
      return;
   }

   if (arg != "") {
      ob = this_player()->query_environment()->present(arg);
      if (!ob) {
         write(arg + " is not here!\n");
         ob = nil;
      } else {
         write(object_name(ob) + "(" + ob->query_name() + "):");
      }
   } else {
      ob = this_player();
   }

   if (ob) {
      stat_abrvs = ( { "str", "int", "wis", "dex", "con", "cha" } );

      stat_names = ( {
         "strength    ", "intelligence", "wisdom      ", "dexterity   ",
         "constitution", "charisma    ",
      } );
      j = 0;

      write("                        stat   base   bonus    max\n");
      write("---------------------------------------------------\n");
      sz = sizeof(stat_names);
      for (i = 0; i < sz; i++) {
         write("\t" + capitalize(stat_names[i]) + " :   " +
            ob->query_stat(stat_abrvs[i]) +
            "\t" + ob->query_base_stat(stat_abrvs[i]) +
            "\t" + ob->query_bonus_stat(stat_abrvs[i]) +
            "\t" + ob->query_race_object()->
            query_base_stat_maximum(stat_abrvs[i]) +
            "\n");
         ++j;

         if (j == 3) {
            write("\n");
            j = 0;
         }
      }

      stat = ob->query_hp();
      max_stat = ob->query_max_hp();
      write("\n\t" + "Hit points   :  " + stat + "/" + max_stat + "\n");
      stat = ob->query_mana();
      max_stat = ob->query_max_mana();
      write("\t" + "Mana         :  " + stat + "/" + max_stat + "\n");
      stat = ob->query_end();
      max_stat = ob->query_max_end();
      write("\t" + "Endurance    :  " + stat + "/" + max_stat + "\n");
   }
}
