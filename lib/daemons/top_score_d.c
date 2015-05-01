#define DATAFILE "/daemons/data/top_score_d.o"
#define DATABASE "/daemons/data/top_score.db"

mapping top_scores;

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);
}

private int use_sqlite3(void) {
#ifdef LPC_EXT_SQLITE3
   return 1;
#else
   return 0;
#endif
}

private void init_storage(void) {
   if (use_sqlite3()) {
      sqlite3_exec(DATABASE, "create table if not exists top_score(" +
         "id integer primary key autoincrement," +
         "name text not null, xp int not null," +
         "kills int not null, killed int not null," +
         "quests int not null );");
   } else {
      if (nilp(top_scores)) {
         top_scores = ([ ]);
      }
   }
}

void create(void) {
   if (!use_sqlite3() && file_exists(DATAFILE)) {
      restore_me();
   }

   init_storage();
}

private int record_exists(object player) {
   string name;

   name = player->query_Name();
   init_storage();

   if (use_sqlite3()) {
      mixed **record;
      record = sqlite3_select(DATABASE,
         "select name from top_score where name = '" + name + "';");
      return !nilp(record) && sizeof(record) && record[0][0] == name;
   }

   return !nilp(top_scores[name]);
}

private void update_map(object player) {
   init_storage();
   top_scores[player->query_Name()] = ({ player->query_expr(),
      player->query_kills(), player->query_killed(),
      sizeof(player->query_quests_completed()) });
   save_me();
}

private void insert(object player) {
   if (use_sqlite3()) {
      sqlite3_exec(DATABASE, "insert into top_score (name, xp, kills, " +
         "killed, quests) values ('" + player->query_Name() +
         "', " + player->query_expr() + ", " +
         player->query_kills() + ", " + player->query_killed() +
         ", " + sizeof(player->query_quests_completed()) + ");");
      return;
   }

   update_map(player);
}

private void update(object player) {
   if (use_sqlite3()) {
      sqlite3_exec(DATABASE, "update top_score " +
         "set xp = " + player->query_expr() + ", " +
         "kills = " + player->query_kills() + ", " +
         "killed = " + player->query_killed() + ", " +
         "quests = " + sizeof(player->query_quests_completed()) + " " +
         "where name = '" + player->query_Name() + "';");
      return;
   }

   update_map(player);
}

int save(object player) {
   if (player->query_Name() == "Who" || query_guest(player)) {
      return 0;
   }
   if (record_exists(player)) {
      update(player);
      return 1;
   }

   insert(player);
   return 0;
}

private void delete(object player) {
   if (use_sqlite3()) {
      sqlite3_exec(DATABASE, "delete from top_score where name = '" +
         player->query_Name() + "';");
      return;
   }

   top_scores[player->query_Name()] = nil;
   save_me();
}

int remove(object player) {
   if (record_exists(player)) {
      delete(player);
      return 1;
   }

   return 0;
}

mixed **get(varargs string order_by) {
   mixed **top_score_data;
   string name, sql, *names;
   int i, dim;

   init_storage();

   if (use_sqlite3()) {
      sql = "select name,xp,kills,killed,quests from top_score " +
         "where name not in ('Who','Guest')";

      if (!empty_str(order_by)) {
         sql += " order by " + order_by + ";";
      }

      top_score_data = sqlite3_select(DATABASE, sql);
      return top_score_data;
   }

   names = bubblesort(map_indices(top_scores));
   dim = sizeof(names);
   top_score_data = allocate(dim);
   for (i = 0; i < dim; i++) {
      name = names[i];
      top_score_data[i] = ({
         name,
         top_scores[name][0],
         top_scores[name][1],
         top_scores[name][2],
         top_scores[name][3]
      });
   }

   return top_score_data;
}

