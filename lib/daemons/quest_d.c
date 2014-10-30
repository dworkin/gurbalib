mapping quests, levels;

#define DATAFILE "/daemons/data/quest_d.o"

/* Example of the quests file.
<quests>
   <quest>
      <domain>newbie</domain>
      <level>1</level>
      <name>NewbieVille</name>
      <file>/domains/newbie/rooms/quest.c</file>
   </quest>
   <quest>
      <domain>2.4.5</domain>
      <level>2</level>
      <name>OrcSlayer</name>
      <file>/domains/2.4.5/monsters/leo.c</file>
   </quest>
</quests>
*/
#define QUEST_DATA "/data/quests/quests"

#define QUEST_GRAMMAR "\
whitespace = /[\n\b\r\t ]+/  \
string = /[a-zA-Z0-9~_\.\/]+/ \
number = /[0-9]+/ \
S: '<quests>' questnodes '</quests>'  \
questnodes: questnode \
questnodes: questnodes questnode \
questnode: '<quest>' '<domain>' string '</domain>' \
'<level>' string '</level>' '<name>' string '</name>' \
'<file>' string '</file>' '</quest>' ? parse_quest_node \
"

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);
}

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

void rehash(void) {
   mixed *parsed;
   if (!quests) {
      quests = ([]);
   }
   if (file_exists(DATAFILE)) {
      restore_me();
   }
   if (file_exists(QUEST_DATA)) {
      parsed = parse_string(QUEST_GRAMMAR, read_file(QUEST_DATA));
   }
   save_me();
}

int add_quest(string name, int level, string domain) {
   int i, max, index;
   string *keys;

   if (!levels) {
      levels = ([]);
   }

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
   if (!quests) {
      quests = ([]);
   }
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
   write("Level:\tQuest:\t\tDomain:\n");
   write("------------------------------------------------\n");

   for (i = 0; i < max; i++) {
      if (keys[i] && levels[keys[i]]) {
         write(levels[keys[i]] + "\t" + keys[i] + "\t" + quests[keys[i]] +
            "\n");
      }
   }
}

static mixed *parse_quest_node(mixed * node) {
   int level;

   if (sizeof(node) == 14) {
      sscanf(node[5], "%d", level);
      if (!is_quest(node[8]) && file_exists(node[11])) {
         add_quest(node[8], level, node[2]);
      }
   }
   return node;
}

void create(void) {
   rehash();
}
