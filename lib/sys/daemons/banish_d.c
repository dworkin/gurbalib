string *banished_names;

#define BAN_DIR     "/data/banished/"

#ifndef SYS_RESERVED_NAMES                                 
#define SYS_RESERVED_NAMES ({ "kernel", "system", "network", "wizard", "wiz",\
    "game", "2.4.5", "boothill", "required", "gurba", "test", "nokicliffs",\
    "newbie"})
#endif               

void create(void) {
   mixed *list;

   banished_names = SYS_RESERVED_NAMES;          
   list = get_dir(BAN_DIR + "*");
   banished_names |= list[0];                  
}

string *query_banished_names(void) {
   return banished_names;
}

int is_banished(string name) {
   if (member_array(name, banished_names) != -1) {
      return 1;
   }

   return 0;
}

int banish_name(string str) {
   if (!require_priv("wizard")) {
      error("Illegal use of banish_d");
      return 0;
   }

   if (str == "") {
      return 0;
   }

   str = lowercase(str);

   if (file_exists(BAN_DIR + str) ||
      (!unguarded("write_file", BAN_DIR + str, ctime(time()) + "\tby:  " +
         this_player()->query_name() + "\n"))) {
      return 0;
   }

   create();
   return 1;
}

int unbanish_name(string str) {
   if (!require_priv("wizard")) {
      error("Illegal use of banish_d");
      return 0;
   }

   str = lowercase(str);

   if (file_exists(BAN_DIR + str)) {
      unguarded("remove_file", BAN_DIR + str);
   }
   create();
   return 1;
}
