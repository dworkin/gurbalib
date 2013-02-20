void usage() {
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
   lines += ({ "\tskilladm remove english" });
   lines += ({ "\tskilladm add dodge" });
   lines += ({ "See also:" });
   lines += ({ "\tskills, aliasadm, coloradm, emoteadm" });

   this_player()->more(lines);
}

void main(string str) {
   string cmd, skill;
   string *skills;
   int i, max;

   if (!str || str == "") {
      skills = SKILL_D->query_skills();
      max = sizeof(skills);
      write("Skills:\n");
      for (i = 0; i < max; i++) {
	 write("\t" + skills[i] + "\n");
      }
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (sscanf(str, "%s %s", cmd, skill) != 2) {
      usage();
      return;
   }

   if (!require_priv("system")) {
      write("You must be admin to do that.");
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
   } else if (cmd == "del" || cmd == "delete" || cmd == "rm" || 
      cmd == "remove") {
      if (!SKILL_D->is_skill(skill)) {
	 this_player()->write("That skill does not exist.");
	 return;
      }
      SKILL_D->remove_skill(skill);
      write("Skill removed. ");
   } else {
      usage();
   }
}
