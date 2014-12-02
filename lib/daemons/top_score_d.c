#define DATAFILE "/daemons/data/top_score_d.o"
#define XP_ELEMENT 0
#define KILLS_ELEMENT 1
#define KILLED_ELEMENT 2
#define QUESTS_ELEMENT 3

mapping top_scores;

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);
}

void create(void) {
   if (file_exists(DATAFILE)) {
      restore_me();
   }
}

private void init_top_scores() {
   if (nilp(top_scores)) {
      top_scores = ([ ]);
   }
}

string query_top_scores(void) {
   string  str, name, xp, kills, killed, quests;
   string *names;
   int     i, dim;

   init_top_scores();
   names = bubblesort(map_indices(top_scores));

   str = "TOP SCORES\n";
   str += "**********";
   for (i = 0, dim = sizeof(names); i < dim; i++) {
      name = names[i];
      xp = "" + top_scores[name][XP_ELEMENT];
      kills = "" + top_scores[name][KILLS_ELEMENT];
      killed = "" + top_scores[name][KILLED_ELEMENT];
      quests = "" + top_scores[name][QUESTS_ELEMENT];
      str += "\n" + name + ": " + add_comma(xp) + " ";
      str += "" + add_comma(kills) + "/" + add_comma(killed);
      str += ". " + add_comma(quests);
      str += ".";
   }
   str += "\n";

   return str;
}

void update(object player) {
   string name;
   int xp, kills, killed, quests;
   if (USER_D->find_player(player->query_name()) {
      init_top_scores();
      name = player->query_Name();
      xp = player->query_expr();
      kills = player->query_kills();
      killed = player->query_killed();
      quests = sizeof(player->query_quests_completed());
      top_scores[name] = ({ xp, kills, killed, quests });
      save_me();
   }
}

