
mapping quests, levels;
string *keys;

#define DATAFILE "/daemons/data/quest.o"

int add_quest(string name, int level, string contacts) {
   int i, max, index;

   if (quests[name]) {
      write("I'm sorry but there is already a quest titled: " + name + "\n");
      return 0;
   }

   max = sizeof(keys);
   index = 0;
   for(i=0; i<max; i++) {
      if (level > levels[keys[i]]) {
         index = index + 1;
      }
   }
   /* Put name in keys at index */

   /* Add mapping values */
   levels[name] = level;
   quests[name] = contacts;
}

/* XXX Not done */
int remove_quest(string name) {
}

void list_quests(object thisp) {
   int i, max;

   max = sizeof(keys);
   write("Level: Completed:   Quest:                 Admin\n");
   write("------------------------------------------------\n");
   for(i=0; i<max; i++) {
      write(levels[keys[i]] + "\t" + keys[i] + "\t" + quests[keys[i]] + "\n");
   }
/* XXX Need to add completed stuff */
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
      keys = ({});
      add_quest("NewbieVille",1,"sirdude");
      save_me();
   }
}

