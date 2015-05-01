inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: top" });
   lines += ({ "", "Gives you the Top Scores list. Needs options." });
   this_player()->more(lines);
}

static void main(string str) {
   mixed **top_scores;
   string *lines;
   string  name, xp, kills, killed, quests;
   int i, dim;

   top_scores = TOP_SCORE_D->get(str);
   if (nilp(top_scores)) {
      write("There have been no top scores generated yet. "+
         "Start adventuring!");
      return;
   }
   dim = sizeof(top_scores);

   lines = allocate(dim);

   for (i = 0; i < dim; i++) {
      name = top_scores[i][0];
      xp = add_comma("" + top_scores[i][1]);
      kills = add_comma("" + top_scores[i][2]);
      killed = add_comma("" + top_scores[i][3]);
      quests = add_comma("" + top_scores[i][4]);
      lines[i] = name + ": " + xp + ", " + kills + "/" + killed + ", " +
         quests;
   }

   write("Top scorers:");
   this_player()->more(lines);
}

