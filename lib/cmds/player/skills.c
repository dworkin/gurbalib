inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: skills [-h] [full]" });
   if (query_wizard(this_player())) {
      lines += ({ "Usage: skills [set SKILL VALUE]" });
   }
   lines += ({ "" });
   lines += ({ "List the skills you know, and how well you know it." });
   lines += ({ "Wizards can also use this command to set a skill to a " +
      "specific value" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tfull\tShow all of the skills available on the mud." });
   lines += ({ "Examples:" });
   lines += ({ "\tskills" });
   lines += ({ "\tskills full" });
   if (query_wizard(this_player())) {
      lines += ({ "\tskills set spell/cure 5" });
   }

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "hp");
   add_also("player", "inventory");
   add_also("player", "junk");
   add_also("player", "levels");
   add_also("player", "score");
   add_also("player", "top");

   add_also("wiz", "status");
}

/*
 * An 'advanced' skill command, by Fudge, Sorressean and Aidil
 */

private void show_skills(string * skills) {
   string line, *lines;
   int i, maxi;

   if (sizeof(skills) == 0) {
      write("No skills to display.");
      return;
   }

   lines = ({ });
   maxi = sizeof(skills);
   for (i = 0; i < maxi; i++) {
      line = skills[i] + "                                     ";
      line = line[0..30] + ": " + this_player()->query_skill(skills[i]);
      lines += ({ line });
   }
   this_player()->more(lines);
}

static int filter_skill(string skill, string str) {
   return sscanf(skill, str + "%*s") != 0;
}

static int set_skill(string skill, int value) {
   if (SKILL_D->is_skill(skill)) {
      this_player()->set_skill(skill, value);
      write("Skill: " + skill + ", set to: " + value + "\n");
      return 1;
   } else {
      write("Error: " + skill + " is not a valid skill currently.\n");
   }
   return 0;
}

static void main(string str) {
   string skill, *skills;
   int i, value;

   if (!alsos) {
      setup_alsos();
   }

   /*
    * Check to see if the player wants to see all skills in game
    * If so, we just populate the skills list with the game skills 
    * rather than player skills and show it as normal.
    */

   if (empty_str(str)) {
      skills = this_player()->query_skills();
   } else if (str == "full") {
      skills = SKILL_D->query_skills();

      /* empty our input string, else the remainder of this function will 
       * try to use it as a filter */
      str = "";

   } else if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   } else if (sscanf(str, "set %s %d", skill, value) == 2) {
      if (query_wizard(this_player())) {
         set_skill(skill, value);
         return;
      } else {
         this_player()->more(usage());
         return;
      }
   } else if (sscanf(str, "full %s", str) == 0) {
      /* Filtered list of skills of this_player() */
      skills = this_player()->query_skills();
   } else {
      /* Filtered list of all game skills */
      skills = SKILL_D->query_skills();
   }

   if (!empty_str(str)) {
      /* write("Using " + str + " to filter skills."); */
      skills = filter_array(skills, "filter_skill", this_object(), str);
   }

   show_skills(skills);
}
