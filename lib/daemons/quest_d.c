mapping quests, levels;

#define DATAFILE "/daemons/data/quest.o"

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

   for(i=0; i<max; i++) {
      if (keys[i] && levels[keys[i]]) {
         write(levels[keys[i]] + "\t" + keys[i] + "\t" + quests[keys[i]] + 
            "\n");
      }
   }
}

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);
}

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

void create(void) {
   if (file_exists(DATAFILE)) {
      restore_me();
   } else {
      quests = ([]);
      levels = ([]);
      add_quest("NewbieVille",1,"newbie");
      save_me();
   }
}

