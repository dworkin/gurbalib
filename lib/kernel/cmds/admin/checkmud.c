void usage() {
   string *lines;

   lines = ({ "Usage: checkmud [-h] [TYPE [VALUE]]" });
   lines += ({ "" });
   lines += ({ "Do some basic checking of the mud.  TYPE can be one of the " +
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

int check_file(string filename) {
}

int check_dir(string dirname) {
}

void check_domain(string domainname) {
}

void check_daemon(string daemon) {
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
         check_dir("/cmds/wiz");
         break;
      case "admin":
      case "admins":
         check_dir("/kernel/cmds/admin");
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
         check_dir("/kernel/cmds/admin");
         break;
   }
}

void do_full_check() {
   check_command("");
   check_daemon("");
   check_domain("");
}

void main(string str) {
   string type, value;

   write("XXX This is a work in progress.\n");

   if (!require_priv("system")) {
      write("You need admin permissions to do that.");
      return;
   }

   if (!str || (str == "")) {
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
   switch(type) {
      "domain":
      "domains":
         check_domain(value);
         break;
      "cmd":
      "cmds":
      "commands":
      "command":
         check_command(value);
         break;
      "daemon":
      "daemons":
         check_daemon(value);
         break;
      default:
         usage();
         break;
   }
}
