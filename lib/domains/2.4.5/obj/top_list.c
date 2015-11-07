inherit "/std/sign";


void setup(void) {
   set_id("list", "top", "top players", "top list", "list of top players");
   set_short("A list of the top players");
   set_gettable(1);
   set_value(5);
   set_weight(1);

   set_message("#query_long");
}

string query_long() {
   mixed **top_scores;
   string  name, xp, kills, killed, quests, *lines, stuff;
   int i, dim;

   top_scores = TOP_SCORE_D->get("");
   if (nilp(top_scores)) {
      return "There have been no top scores generated yet. " +
         "Start adventuring!";
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

   stuff = implode(lines, "\n");

   return stuff;
}

