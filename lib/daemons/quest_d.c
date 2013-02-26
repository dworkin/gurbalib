mapping quests;
string *keys;

#define DATAFILE "/daemons/data/quest.o"

int add_quest(string name, int level, string contacts) {
   int i, max, index;

   if (exists(quests{name})) {
      write("I'm sorry but there is already a quest titled: " + name + "\n");
      return 0;
   }

   max = sizeof(keys);
   index = 0;
   for(i=0;i<max;i++) {
      if (level > quests{keys[i]->level}) {
         index = index + 1;
      }
   }
   /* Put name in keys at index */

   /* Add mapping values */
   quests{name}->level = level;
   quests{name}->contacts = contacts;

}

int remove_quest(string name) {
}

void list_quests() {
}

void create(void) {
   if (file_exists(DATAFILE) {
      restore_me();
   } else {
   quests = ([]);
   keys = ();
   add_quest("NewbieVille",1,"sirdude");
   save_me();
}

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);

}

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

