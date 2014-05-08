inherit M_COMMAND;

void usage() {
   string *lines;

   if (query_wizard(this_player())) {
      lines = ({ "Usage: score [-h] [-q] [PLAYER]" });
      lines += ({ "" });
      lines += ({ "Gives you basic stats about player PLAYER." });
      lines += ({ "If no player is given give your stats." });
      lines += ({ "" });
      lines += ({ "Options:" });
      lines += ({ "\t-h\tHelp, this usage message." });
      lines += ({ "Examples:" });
      lines += ({ "\tscore" });
      lines += ({ "\tscore sirdude" });
      lines += ({ "See also:" });
      lines += ({ "\thp, inventory, junk, levels, skills, status" });
   } else {
      lines = ({ "Usage: score [-h]" });
      lines += ({ "" });
      lines += ({ "Gives you basic stats about your character." });
      lines += ({ "" });
      lines += ({ "Options:" });
      lines += ({ "\t-h\tHelp, this usage message." });
      lines += ({ "\t-q\tAlso display quests you have completed." });
      lines += ({ "Examples:" });
      lines += ({ "\tscore" });
      lines += ({ "See also:" });
      lines += ({ "\thp, inventory, junk, levels, skills" });
   }

   this_player()->more(lines);
}

static void main(string str) {
   int mh, h, expr, level, quest, mm, m, me, e, ac, i;
   mixed *money;
   object obj;
   string age;
   string *l;

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

   if (!empty_str(str)) {
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

   l = ({ "[ " + obj->query_name() + " ] " + obj->query_title() });
   l += ({ "A " + obj->query_gender() + " " + obj->query_race() +
         " who is " + obj->query_status() + "\n" });
   l += ({ "Strength    :  " + obj->query_stat("str") +
         "\t\t" + "Hit points  :   " + h + "/" + mh });
   l += ({ "Intelligence:  " + obj->query_stat("int") +
         "\t\t" + "Endurance   :   " + e + "/" + me });
   l += ({ "Wisdom      :  " + obj->query_stat("wis") +
         "\t\t" + "Mana        :   " + m + "/" + mm });
   l += ({ "Dexterity   :  " + obj->query_stat("dex") +
         "\t\t" + "Armor class :   " + ac });
   l += ({ "Constitution:  " + obj->query_stat("con") +
         "\t\t" + "Level       :   " + level });
   l += ({ "Charisma    :  " + obj->query_stat("cha") +
         "\t\t" + "Experience  :   " + add_comma("" + expr) + "\n" });

   l += ({ "Kills: " + add_comma("" + obj->query_kills()) + " " +
		"Killed: " + add_comma("" + obj->query_killed()) + "\n" });

   l += ({ "Age:" + age + "\t" + "Money:" });

   for (i = 0; i < sizeof(money); i++) {
      l += ({ "\t\t\t\t" + capitalize(money[i][0]) + ": " +
			add_comma("" + money[i][1]) });
   }

   if (quest) {
      string *quests;
      int j, k;

      l += ({ "Quests Completed:" });
      quests = this_player()->query_quests_completed();
      if (quests) {
         k = sizeof(quests);
         for (j = 0; j < k; j++) {
            l += ({ "\t" + quests[j] });
         }
      }
   }
   this_player()->more(l);

   return;
}
