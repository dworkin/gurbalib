inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: skilladm [-h] [CMD SKILL]" });
   lines += ({ "" });
   lines += ({ "Used to add, remove or list available skills on the mud." });
   lines += ({ "\tCMD can be: add, remove\n"});
   lines += ({ "If no args are given show all skills." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tskilladm" });
   lines += ({ "\tskilladm remove english" });
   lines += ({ "\tskilladm add dodge" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "skills");

   add_also("admin", "aliasadm");
   add_also("admin", "coloradm");
   add_also("admin", "emoteadm");
   add_also("admin", "questadm");
}

static void main(string str) {
   string cmd, skill, *skills;
   int i, max;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      skills = SKILL_D->query_skills();
      max = sizeof(skills);
      write("Skills:\n");
      for (i = 0; i < max; i++) {
         write("\t" + skills[i] + "\n");
      }
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "%s %s", cmd, skill) != 2) {
      this_player()->more(usage());
      return;
   }

   cmd = lowercase(cmd);
   if (cmd == "add") {
      if (SKILL_D->is_skill(skill)) {
         this_player()->write("That skill already exists.");
         return;
      }
      SKILL_D->add_skill(skill);
      write("Skill added. ");
   } else if ((cmd == "del") || (cmd == "delete") || (cmd == "rm") || 
      (cmd == "remove")) {

      if (!SKILL_D->is_skill(skill)) {
         this_player()->write("That skill does not exist.");
         return;
      }
      SKILL_D->remove_skill(skill);
      write("Skill removed. ");
   } else {
      this_player()->more(usage());
   }
}
