void usage() {
   string *lines;

   lines = ({ "Usage: git -h [push] [pull] [commit [-m \"Message\"]] " +
      "[status] [dir]" });
   lines += ({ " " });
   lines += ({ "An interface to the external git repository system." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-m \"Message\"\tUsed when committing changes, Message is " +
      "a brief" });
   lines += ({ "\t\tdescription of changes you are committing." });
   lines += ({ "\tstatus [dir]\tGives you a summary of uncommitted " +
      "changes you have made." });
   lines += ({ "\tpull [dir]\tPulls the latest updates from the external " +
      "repository." });
   lines += ({ "\tpush [dir]\tPushes your commits to the external " +
      "repository." });
   lines += ({ "\tcommit -m \"Message\" [dir]\tCommit changes you have made " +
      "back" });
   lines += ({ "\t\tto the external repository." });
   lines += ({ "[dir] is optional, and will use the current directory" +
      " if not given." });
   lines += ({ "Examples:" });
   lines += ({ "See also:" });

   this_player()->more(lines);
}

void main(string str) {
   string cmd, dir, arg, message;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (!str || (str == "")) {
      usage();
      return;
   }
   if (sscanf(str,"-h%s", cmd)) {
      usage();
      return;
   }
   
   if (sscanf(str,"%s %s", cmd, dir) != 2) {
      cmd = str;
      dir = "";
   }

   if (cmd == "push") {
   } else if (cmd == "pull") {
   } else if (cmd == "status") {
   } else if (cmd == "commit") {
      if (sscanf(dir,"-m \"%s\" %s", message, arg) > 0) {
         dir = arg;
      } else if (sscanf(dir,"-m \"%s\"", message) > 0) {
         dir = "";
      } else {
         usage();
         return;
      }
   } else {
      usage();
      return;
   }

   dir = normalize_path(dir, this_player()->query_env("cwd"));

   if (call_git(this_player(),cmd,dir,message)) {
   } else {
      usage();
      return;
   } 
}
