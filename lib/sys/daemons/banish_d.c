string *banished_names;

#define BAN_DIR     "/data/banished/"

void create() {
   mixed *list;

   list = get_dir(BAN_DIR + "*");
   banished_names = list[0];
   banished_names |= SYS_BANNED_NAMES;
}

string *query_banished_names() {
   return (banished_names);
}

int is_banished(string name) {
   if (member_array(name, banished_names) != -1)
      return 1;

   return 0;
}

int banish_name(string str) {
   if (!require_priv("wiz"))
      error("Illegal use of banish_d");

   if (str == "")
      return 0;

   str = lowercase(str);

   if (file_exists(BAN_DIR + str) ||
      (!unguarded("write_file", BAN_DIR + str, ctime(time()) + "\tby:  " +
	    this_player()->query_name() + "\n")))
      return 0;

   create();
   return 1;
}

int unbanish_name(string str) {
   if (!require_priv("wiz"))
      error("Illegal use of banish_d");

   str = lowercase(str);

   if (file_exists(BAN_DIR + str)) {
      unguarded("remove_file", BAN_DIR + str);
      create();
      return 1;
   }
   return 0;
}
