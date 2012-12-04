void usage() {
   string *lines;

   lines = ({ "Usage: skills [-h] [full]" });
   lines += ({ "" });
   lines += ({ "List the skills you know" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tfull\tShow all of the skills available on the mud." });
   lines += ({ "Examples:" });
   lines += ({ "\tskills" });
   lines += ({ "\tskills full" });
   lines += ({ "See also:" });
   lines += ({ "\thp, inventory, levels, score" });

   this_player()->more(lines);
}

/*
 * An 'advanced' skill command, by Fudge, Sorressean and Aidil
 */
#undef DEBUG_SKILLS

static void DBM(string str) {
#ifdef DEBUG_SKILLS
   write(str);
#endif
}

private void show_skills(string * skills) {
   string line;
   string *lines;
   int i;

   if (sizeof(skills) == 0) {
      write("No skills to display.");
      return;
   }

   lines = ( { } );
   for (i = 0; i < sizeof(skills); i++) {
      line = skills[i] + "                                     ";
      line = line[0..30] + ": " + this_player()->query_skill(skills[i]);
      lines += ( { line } );
   }
   this_player()->more(lines);
}

static int filter_skill(string skill, string str) {
   return sscanf(skill, str + "%*s") != 0;
}

void main(string str) {
   string *skills;
   int i;

   /*
    * Check to see if the player wants to see all skills in game
    * If so, we just populate the skills list with the game skills 
    * rather than player skills and show it as normal.
    */

   if (str == "full") {
      /* all game skills */
      DBM("Showing all existing skills.");
      skills = SKILL_D->query_skills();
      /*
       * empty our input string, else the remainder of this function will 
       * try to use it as a filter
       */
      str = "";
   } else if ((str == "") || (!str)) {
      /* All skills of this_player() */
      skills = this_player()->query_skills();
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   } else if (sscanf(str, "full %s", str) == 0) {
      /* Filtered list of skills of this_player() */
      skills = this_player()->query_skills();
      DBM("Filtering all of your skills using " + str + ".");
   } else {
      /* Filtered list of all game skills */
      skills = SKILL_D->query_skills();
   }

   if (str && str != "") {
      DBM("Using " + str + " to filter skills.");
      skills = filter_array(skills, "filter_skill", this_object(), str);
   }

   show_skills(skills);
}
