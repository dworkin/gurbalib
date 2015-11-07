mapping levels;

static void save_me(void) {
   unguarded("save_object", "/sys/daemons/data/log_d.o");
}

static void restore_me(void) {
   unguarded("restore_object", "/sys/daemons/data/log_d.o");
}

string *show_log_levels(void) {
   string *logs, *keys;
   int x, max;

   logs = ({ "Log Levels:" });
   logs += ({ "\tdefault: " + levels["default"] });
   keys = map_indices(levels);
   max = sizeof(keys);
   for (x = 0; x < max; x++) {
      if (keys[x] != "default") {
         logs += ({ "\t" + keys[x] + ": " + levels[keys[x]] });
      }
   }

   return logs;
}

static void create(void) {
   levels = ([ ]);
   levels["default"] = 1;

   restore_me();
   save_me();
}

int set_log_level(string name, mixed x) {

   if (!query_admin(this_player())) {
      return 0;
   }

   if (x == "default") {
      if (name == "default") {
         return 0;
      }
      levels[name] = nil;
   } else {
      if (!intp(x)) {
         return 0;
      }
      levels[name] = x;
   }
   save_me();
   return 1;
}

int query_log_level(string name) {
   if (member_map(name, levels)) {
      return levels[name];
   } else {
      return levels["default"];
   }
}

int check_level(string name, int x) {
   if (member_map(name, levels)) {
      if (levels[name] >= x) {
         return 1;
      } else {
         return 0;
      }
   } else {
      if (levels["default"] >= x) {
         return 1;
      } else {
         return 0;
      }
   }
}

int write_log(string log, string message, varargs int level) {
   string basedir, user;

   user = owner_object(previous_object());

   if (sscanf(log, "%*s/..%*s") != 0) {
      error("illegal log name");
      return 0;
   }

   if (!level) {
      level = 1;
   }

   if (!check_level(log, level)) {
      return 0;
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
            basedir = "/logs/nobody/";
         }
         break;
   }

   unguarded("write_file", basedir + log, message);
   return 1;
}
