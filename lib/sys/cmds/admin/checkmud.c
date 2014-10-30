inherit M_COMMAND;

int debug, errors;

void usage(void) {
   string *lines;

   lines = ({ "Usage: checkmud [-h] [TYPE [VALUE]]" });
   lines += ({ "" });
   lines += ({ "Do some basic checking of the mud, to find any files that " });
   lines += ({ "obviously do not compile.  For extensive testing of specific " 
      });
   lines += ({ "files use the check command instead.  TYPE can be one of the " +
      "following:" });
   lines += ({ "\tcmds domain daemon" });
   lines += ({ "If TYPE == cmds then value can be:" });
   lines += ({ "\tplayer wiz admin guild monster spells verb" });
   lines += ({ "If TYPE == domain then value can be an existing domain." });
   lines += ({ "If TYPE == daemon then value can be an existing daemon." });
 
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcheckmud cmds" });
   lines += ({ "\tcheckmud cmds wiz" });
   lines += ({ "\tcheckmud domains newbie" });
   lines += ({ "\tcheckmud daemons time_d" });
   lines += ({ "See also:" });
   lines += ({ "\tcheck, clean, clone, dest, eval, graph, rebuild, " +
         "update, warmboot" });

   this_player()->more(lines);
}

int valid_file(string filename) {
   int x;

   x = strlen(filename) - 2;
   if (x < 1) {
      return 0;
   }

   write("Checking: " + filename + "\n");

   if (filename[x..] == ".c") {
      return 1;
   }

   return 0;
}

int check_file(string filename) {
   object obj;

   obj = compile_object(filename);

   if (obj) {
      return 1;
   }

   errors = errors + 1;
   write("Error in file: " + filename + "\n");

   return 0;
}

/* Find all of the .c files in a dir and check them */
int check_dir(string dirname) {
   mixed *files;
   string *names;
   int max, x;
   string tmp;

   files = get_dir(dirname + "/*");
   names = files[0];
   max = sizeof(names);
   
   for(x = 0; x < max; x++) {
      tmp = dirname + "/" + names[x];
      if (file_exists(tmp) == -1) {
         check_dir(tmp);
      } else if (valid_file(tmp)) {
         check_file(tmp);
      } else {
         if (debug) {
            write("Unrecongnized file: " + tmp + " skipping it.\n");
         }
      }
   }
}

void check_domain(string domainname) {
   if (file_exists("/domains/" + domainname) == -1) {
      check_dir("/domains/" + domainname);
   } else {
      write("No such domain: " + domainname + "\n");
   }
}

void check_daemon(string daemon) {
   int done;

   if (!daemon || daemon == "") {
      check_dir("/kernel/daemons");
      check_dir("/sys/daemons");
      check_dir("/daemons");
      done = 1;
   } else {
      if (file_exists("/kernel/daemons/" + daemon)) {
         check_dir("/kernel/daemons/" + daemon);
         done = 1;
      }
      if (file_exists("/sys/daemons/" + daemon)) {
         check_dir("/sys/daemons/" + daemon);
         done = 1;
      }
      if (file_exists("/daemons/" + daemon)) {
         check_dir("/daemons/" + daemon);
         done = 1;
      }
      if (!done) {
         write("Unable to find daemon: " + daemon + "\n");
      }
   }
}

void check_command(string type) {
   switch(type) {
      case "player":
      case "players":
         check_dir("/cmds/player");
         break;
      case "wiz":
      case "wizard":
      case "wizards":
         check_dir("/sys/cmds/wiz");
         break;
      case "admin":
      case "admins":
         check_dir("/sys/cmds/admin");
         break;
      case "monster":
      case "monsters":
         check_dir("/cmds/monster");
         break;
      case "guild":
      case "guilds":
         check_dir("/cmds/guild");
         break;
      case "spells":
      case "spell":
         check_dir("/cmds/spells");
         break;
      case "verb":
         check_dir("/cmds/verb");
         break;
      default:
         check_dir("/cmds/verb");
         check_dir("/cmds/spells");
         check_dir("/cmds/guild");
         check_dir("/cmds/monster");
         check_dir("/cmds/player");
         check_dir("/sys/cmds/wiz");
         check_dir("/sys/cmds/admin");
         break;
   }
}

void do_full_check(void) {
   check_command("");
   check_daemon("");
   check_domain("");
}

static void main(string str) {
   string type, value;
   debug = 0;

   if (empty_str(str)) {
      do_full_check();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (sscanf(str, "%s %s",type, value) == 2) {
   } else {
      type = str;
   }
   if (!value) {
      value = "";
   }
   switch(type) {
      case "domain":
      case "domains":
         check_domain(value);
         break;
      case "cmd":
      case "cmds":
      case "commands":
      case "command":
         check_command(value);
         break;
      case "daemon":
      case "daemons":
         check_daemon(value);
         break;
      default:
         usage();
         break;
   }
}
