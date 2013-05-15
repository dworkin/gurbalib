void usage() {
   string *lines;

   lines = ({ "Usage: questadm [-h] [remove QUEST]" });
   lines = ({ "Usage: questadm [-h] [add QUEST LEVEL CONTACTS]" });
   lines += ({ "" });
   lines += ({ "Used to add, remove or list available quests on the mud." });
   lines += ({ "\tQUEST is a name for your quest, \n"});
   lines += ({ "\tLEVEL is a recomended level for your quest, \n"});
   lines += ({ "\tCONTACTS is a list of wizards that are incharge of " +
      "the quest.\n"});
   lines += ({ "If no args are given show all quests." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tquestadm remove NewbieVille" });
   lines += ({ "\tquestadm add NewbieVille 1 sirdude" });
   lines += ({ "\tquestadm add NewbieVille 1 sirdude,fudge" });
   lines += ({ "See also:" });
   lines += ({ "\taliasadm, coloradm, emoteadm, quests, skilladm, skills" });

   this_player()->more(lines);
}

void main(string str) {
   string cmd, rest, questname, contacts;
   int i, max, level;

   if (!require_priv("system")) {
      write("You must be admin to do that.");
      return;
   }

   if (!str || str == "") {
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
      if (sscanf(rest,"%s %d %s",questname, level, contacts)) {
         QUEST_D->add_quest(questname,level,contacts);
      } else {
         usage();
         return;
      }
   } else if (cmd == "del" || cmd == "delete" || cmd == "rm" || 
      cmd == "remove") {
      if (!QUEST_D->is_quest(rest)) {
	 this_player()->write("That is not a valid quest.");
	 return;
      }
      if (QUEST_D->remove_skill(rest)) {
         write("Quest: " + rest + " removed. ");
      }
   } else {
      usage();
   }
}
