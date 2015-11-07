mapping quests, levels;

#define DATAFILE "/daemons/data/quest_d.o"

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);
}

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

int add_quest(string name, int level, string domain) {
   int i, max, index;
   string *keys;

   if (quests[name]) {
      write("I'm sorry but there is already a quest titled: " + name + "\n");
      return 0;
   }

   /* Add mapping values */
   levels[name] = level;
   quests[name] = domain;
   save_me();
   return 1;
}

int is_quest(string name) {

   if (quests[name]) {
      return 1;
   }
   return 0;
}

int remove_quest(string name) {
   if (quests[name]) {
      levels[name] = nil;
      quests[name] = nil;
      save_me();
      return 1;
   }
   return 0;
}

void list_quests(object thisp) {
   int i, max;
   string *keys;

   keys = map_indices(levels);
   max = sizeof(keys);
   write("Level:  Quest:                           Domain:\n");
   write("------------------------------------------------\n");

   for (i = 0; i < max; i++) {
      if (keys[i] && levels[keys[i]]) {
         write(levels[keys[i]] + "\t" + keys[i] + "\t" + quests[keys[i]] +
            "\n");
      }
   }
}

void create(void) {
   quests = ([]);
   levels = ([]);

   if (file_exists(DATAFILE)) {
      restore_me();
   } else {
      if (file_exists("/domains/newbie/rooms/quest.c")) {
         add_quest("NewbieVille", 1, "newbie");
      }

      if (file_exists("/domains/boothill/rooms/escape.c")) {
         add_quest("AbandonedMine", 1, "boothill");
      }

      if (file_exists("/domains/2.4.5/rooms/wiz_hall.c")) {
         add_quest("OrcSlayer", 2, "2.4.5");
      }
   }
}
