inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: top" });
   lines += ({ "" });
   lines += ({  "Gives you the Top Scores list. It has the following fields:"
      });
   lines += ({ "\tExperience, kills, quests completed" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\ttop" });
   lines += ({ "See also:" });

   if (query_wizard(this_player())) {
      lines += ({ "\thp, inventory, junk, levels, score, skills, status" });
   } else {
      lines += ({ "\thp, inventory, junk, levels, score, skills" });
   }

   this_player()->more(lines);
}

static void main(string str) {
   mixed **top_scores;
   string  name, xp, kills, killed, quests, *lines;
   int i, dim;

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   top_scores = TOP_SCORE_D->get(str);
   if (nilp(top_scores)) {
      write("There have been no top scores generated yet. "+
         "Start adventuring!");
      return;
   }
   dim = sizeof(top_scores);

   lines = allocate(dim + 2);

   lines[0] = "Top Ten Players list";
   lines[1] = "-------------------------------------------";

   for (i = 0; i < dim; i++) {
      name = top_scores[i][0];
      xp = add_comma("" + top_scores[i][1]);
      kills = add_comma("" + top_scores[i][2]);
      killed = add_comma("" + top_scores[i][3]);
      quests = add_comma("" + top_scores[i][4]);
      lines[i + 2] = name + ": " + xp + ", " + kills + "/" + killed + ", " +
         quests;
   }

   this_player()->more(lines);
}

