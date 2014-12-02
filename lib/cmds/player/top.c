inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: top" });
   lines += ({ "", "Gives you the Top Scores list. Needs options." });
   this_player()->more(lines);
}

static void main(string str) {
   this_player()->more(explode(TOP_SCORE_D->query_top_scores(), "\n"));
}

