int minlevel;

static void save_me() {
   unguarded("save_object", "/sys/daemons/data/logd.o");
}

static void restore_me() {
   unguarded("restore_object", "/sys/daemons/data/logd.o");
}

static void create() {
   minlevel = 3;
   restore_me();
   save_me();
}

int set_minlog_level(int x) {
   if (query_admin(this_player())) {
      minlevel = x;
      save_me();
      return 1;
   }

   return 0;
}

int write_log(string log, string message, varargs int level) {
   string basedir, user;

   user = owner_object(previous_object());

   if (sscanf(log, "%*s/..%*s") != 0) {
      error("illegal log name");
      return 0;
   }

   if (!level) {
      level = 3;
   }

   switch (user) {
      case "system":
      case "kernel":
      case "game":
	 basedir = "/logs/";
	 break;
      default:
	 if (unguarded("file_exists", WIZ_DIR + "/" + user + "/logs") == -1) {
	    basedir = WIZ_DIR + "/" + user + "/logs/";
	 } else if (unguarded("file_exists", DOMAINS_DIR + "/" + user + 
            "/logs") == -1) {
	    basedir = DOMAINS_DIR + "/" + user + "/logs/";
	 } else {
	    basedir = "/logs/nobody";
	 }
	 break;
   }

   if (level >= minlevel) {
      unguarded("write_file", basedir + log, message);
      return 1;
   }

   return 0;
}
