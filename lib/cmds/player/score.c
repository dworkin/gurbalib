void usage() {
   string *lines;

   if (query_wizard(this_player())) {
      lines = "Usage: score [-h] [-q] [PLAYER]" });
      lines += ({ "Gives you basic stats about player PLAYER." });
      lines += ({ "If no player is given give your stats." });
      lines += ({ "Options:" });
      lines += ({ "\t-h\tHelp, this usage message." });
      lines += ({ "Examples:" });
      lines += ({ "\tscore" });
      lines += ({ "\tscore sirdude" });
      lines += ({ "See also: hp, inventory, levels, skills, status" });
   } else {
      lines = ({ "Usage: score [-h]" });
      lines += ({ "Gives you basic stats about your character." });
      lines += ({ "Options:" });
      lines += ({ "\t-h\tHelp, this usage message." });
      lines += ({ "\t-q\tAlso display quests you have completed." });
      lines += ({ "Examples:" });
      lines += ({ "\tscore" });
      lines += ({ "See also: hp, inventory, levels, skills" });
   }

   this_player()->more(lines);
}

void main(string str) {
   int mh, h, expr, level, quest;
   int mm, m, me, e;
   int ac, i;
   mixed *money;
   object obj;
   string age;

   quest = 0;
   if (str == "-q") {
      str = "";
      quest = 1;
   } else if (sscanf(str, "-q %s", str)) {
      quest = 1;
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (str && str != "") {
      if (query_wizard(this_player())) {
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
   mh = obj->query_max_hp();
   h = obj->query_hp();
   mm = obj->query_max_mana();
   m = obj->query_mana();
   me = obj->query_max_end();
   e = obj->query_end();
   expr = obj->query_expr();
   ac = obj->query_defense();
   level = obj->query_level();
   age = obj->query_age();

   write("[ " + obj->query_name() + " ] " + obj->query_title() + "\n");
   write("A " + obj->query_gender() + " " + obj->query_race() + 
      " who is " + obj->query_status() + "\n");
   write("Strength    :  " + obj->query_stat("str") +
      "\t\t" + "Hit points  :   " + h + "/" + mh + "\n");
   write("Intelligence:  " + obj->query_stat("int") +
      "\t\t" + "Endurance   :   " + e + "/" + me + "\n");
   write("Wisdom      :  " + obj->query_stat("wis") +
      "\t\t" + "Mana        :   " + m + "/" + mm + "\n");
   write("Dexterity   :  " + obj->query_stat("dex") +
      "\t\t" + "Armor class :   " + ac + "\n");
   write("Constitution:  " + obj->query_stat("con") +
      "\t\t" + "Level       :   " + level + "\n");
   write("Charisma    :  " + obj->query_stat("cha") +
      "\t\t" + "Experience  :   " + expr + "\n\n");
   write("Age:" + age + "\t" + "Money:\n");

   for (i = 0; i < sizeof(money); i++) {
      write("\t\t\t\t" + capitalize(money[i][0]) + ": " + money[i][1] + "\n");
   }

   if (quest) {
      string *quests;
      int j, k;

      write("Quests Completed:\n");
      quests = this_player()->query_quests_completed();
      if (quests) {
	 k = sizeof(quests);
	 for (j = 0; j < k; j++) {
	    write("\t" + quests[j] + "\n");
	 }
      }
   }

   return;
}
