/* Gurbalib command daemon by Aidil@Way of the Force */
#include <privileges.h>

/* Uncomment this to debug things */
/* #define DEBUG_COMMAND_D 1 */

#define SYS_CMDPRIV ([\
      "/sys/cmds/admin/"     : "system",\
      "/sys/cmds/wiz/"       : "wizard",\
      "/cmds/player/"        : "*",\
      "/cmds/guild/fighter/" : "*",\
      "/cmds/spells/"        : "*",\
      "/cmds/monster/"       : "*",\
])

#define DATA_FILE "/sys/daemons/data/command_d.o"
#define secure() require_priv("system")

mapping cmdpriv;
static mapping commands;

void rehash();

static void DBT(string str) {
   mixed verbose;

   if (this_player()) {
      verbose = this_player()->query_env("debug_commands");
      if (stringp(verbose) && (verbose == "on" || verbose == "1")) {
         verbose = 1;
      } else if (!intp(verbose)) {
         verbose = 0;
      }
      if (verbose) {
         this_player()->out(str);
      }
   }
#ifdef DEBUG_COMMAND_D
   console_msg(str);
#endif
}

static int restore_me(void) {
   return unguarded("restore_object", DATA_FILE);
}

static void save_me(void) {
   unguarded("save_object", DATA_FILE);
}

static void create(void) {
   int i, sz;

   restore_me();

   if (!cmdpriv) {
      cmdpriv = ([]);
   }

   save_me();
   rehash();
}

static int access_check(string path) {
   string priv;

   if (cmdpriv[path]) {
      priv = cmdpriv[path];
   } else {
      priv = SYS_CMDPRIV[path];
   }
   return (priv && (priv != "-") && ((priv == "*") || require_priv(priv)));
}

static string file_to_cmdname(string file) {
   string r;

   sscanf(file, "%s.c", r);
   DBT("Adding " + file + " : " + dump_value(r) + "\n");
   return r;
}

void rehash(void) {
   int i, sz;
   string *syspath, *cmds;

   if (!secure()) {
      error("Permission denied.");
   }
   syspath = map_indices(cmdpriv) | map_indices(SYS_CMDPRIV);
   commands = ([]);

   console_msg("Rehashing command paths\n");
   for (i = 0, sz = sizeof(syspath); i < sz; i++) {
      cmds = get_dir(syspath[i] + "*.c")[0];
      cmds = map_array(cmds, "file_to_cmdname", this_object());
      commands[syspath[i]] = cmds;
      console_msg(syspath[i] + "		: " + sizeof(cmds) + "\n");
   }
   DBT(dump_value(commands) + "\n");
   console_msg("Rehash done.\n");
}

object find_command(string cmd, string arg, string *syspath) {
   object cmd_ob;
   int i, sz;

   for (i = 0, sz = sizeof(syspath); (i < sz) && !cmd_ob; i++) {
      DBT("Locating " + cmd + " in " + syspath[i] + ": ");
      if (commands[syspath[i]] && sizeof(commands[syspath[i]] & 
         ({ cmd}))) {
         DBT("found\n");
         if (access_check(syspath[i])) {
            cmd_ob = find_object(syspath[i] + cmd);
            if (!cmd_ob) {
               cmd_ob = unguarded("compile_object", syspath[i] + cmd);
            }
         } else {
            DBT("but no access\n");
         }
      } else {
         DBT("not found\n");
      }
   }

   return cmd_ob;
}

int exec_command(string cmd, string arg, string * syspath) {
   object cmd_ob;

   if (!previous_object() <-"/sys/lib/modules/m_cmds") {
      error("Permission denied.");
   }

   if (cmd) {
      DBT("exec_command: " + cmd + " " + dump_value(syspath) + "\n");
   } else {
      DBT("exec_command: <NIL> " + dump_value(syspath) + "\n");
   }

   if (!cmd || cmd == "") {
      return -1;
   }

   cmd_ob = find_command(cmd, arg, syspath);

   if (cmd_ob && cmd_ob <-M_COMMAND && !function_object("main", cmd_ob)) {
      if (arg) {
      DBT("Calling " + dump_value(cmd_ob) + "->_main( \"" + arg + "\"" +
         ", \"" + cmd + "\" )\n");
      } else {
      DBT("Calling " + dump_value(cmd_ob) + "->_main( <NIL>" + 
         ", \"" + cmd + "\" )\n");
      }
      cmd_ob->_main(arg, cmd);
      return 1;
   } else {
      string msg;

      msg = cmd + " not handled by the command daemon: " +
         dump_value(cmd_ob) + "\n";
      msg += "Reason: ";
      if (!cmd_ob) {
         msg += "no matching .c file";
      } else if (!cmd_ob <-M_COMMAND) {
         msg += ".c file does not inherit m_command";
      } else if (function_object("main", cmd_ob)) {
         msg += "function main() is public";
      } else {
         msg += "unknown";
      }
      msg += "\n";
      DBT(msg);
      return -1;
   }
}

string cmdstats(void) {
   int i, sz;
   string r, *syspath;

   if (!KERNEL() && !SYSTEM()) {
      error("Permission denied.\n");
   }

   syspath = map_indices(cmdpriv) | map_indices(SYS_CMDPRIV);
   r = "";

   for (i = 0, sz = sizeof(syspath); i < sz; i++) {
      r += syspath[i] + " : " + sizeof(commands[syspath[i]]) + "\n";
   }
   return r;
}

int validate_path(string path) {
   return access_check(path);
}

int cmd_path_exists(string path) {
   return cmdpriv[path] || SYS_CMDPRIV[path];
}

/* can only be called from system code, which is trusted with this data
   especially since we return a copy so it can't be modified */
mapping query_cmdpriv(void) {
   if (!KERNEL() && !SYSTEM()) {
      error("Permission denied");
   }

   return SYS_CMDPRIV + cmdpriv;        /* warning, order is important */
}

void add_path(string path, string priv) {
   if (!secure()) {
      error("Permission denied.");
   }
   if (path[0] != '/') {
      error("Invalid path");
   }
   if (path[strlen(path) - 1] != '/') {
      path += "/";
   }
   cmdpriv[path] = priv;
   save_me();
}

void remove_path(string path) {
   if (!secure()) {
      error("Permission denied.");
   }
   cmdpriv[path] = nil;
   save_me();
}

int query_override(string path) {
   return cmdpriv[path] && SYS_CMDPRIV[path];
}

int query_syspath(string path) {
   return SYS_CMDPRIV[path] != nil;
}

int file_is_command(string what) {
   int i, sz;
   string *syspath;

   syspath = map_indices(cmdpriv) | map_indices(SYS_CMDPRIV);

   sz = sizeof(syspath);
   for (i = 0; i < sz; i++) {
      if (strstr(what, syspath[i]) == 0) {
         return 1;
      }
   }
   return 0;
}

int file_is_spell(string what) {
   if (strstr(what, "/cmds/spells/") == 0) {
      return 1;
   }
   return 0;
}
