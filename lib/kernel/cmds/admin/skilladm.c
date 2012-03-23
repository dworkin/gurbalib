void usage() {
   write("Usage: skilladm [-h] [remove SKILL] [add SKILL]\n");
   write("Remove the specified skill, SKILL.\n");
   write("Add the specified skill, SKILL.\n");
   write("If no args are given show all skills.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: skills\n");
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
