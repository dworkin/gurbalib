inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: questadm [-h] [remove QUEST]" });
   lines = ({ "Usage: questadm [-h] [add QUEST LEVEL DOMAIN]" });
   lines += ({ "" });
   lines += ({ "Used to add, remove or list available quests on the mud." });
   lines += ({ "\tQUEST is a name for your quest,"});
   lines += ({ "\tLEVEL is a recommended level for your quest,"});
   lines += ({ "\tDOMAIN is the name of the domain the quest is in."});
   lines += ({ "If no args are given show all quests." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tquestadm remove NewbieVille" });
   lines += ({ "\tquestadm add NewbieVille 1 newbie" });
   lines += ({ "See also:" });
   lines += ({ "\taliasadm, coloradm, emoteadm, quests, skilladm, skills" });

   this_player()->more(lines);
}

static void main(string str) {
   string cmd, rest, questname, domain;
   int i, max, level;

   if (!str || (str == "")) {
      QUEST_D->list_quests(this_player());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (sscanf(str, "%s %s", cmd, rest) != 2) {
      usage();
      return;
   }

   cmd = lowercase(cmd);
   if (cmd == "add") {
      if (sscanf(rest,"%s %d %s",questname, level, domain) == 3) {
         QUEST_D->add_quest(questname, level, domain);
      } else {
         usage();
         return;
      }
   } else if ((cmd == "del") || (cmd == "delete") || (cmd == "rm") || 
      (cmd == "remove")) {

      if (!QUEST_D->is_quest(rest)) {
	 this_player()->write("That is not a valid quest.");
	 return;
      }
      if (QUEST_D->remove_quest(rest)) {
         write("Quest: " + rest + " removed. ");
      }
   } else {
      usage();
   }
}
