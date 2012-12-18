void usage() {
   write("Usage: git -h [push] [pull] [commit [-m \"Message\"]] [status] " +
      "[dir]\n");
   write("An iterface to the external git repository system.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\t-m \"Message\"\tUsed when commiting changes, Message is a brief\n" +
      "\t\tdescription of changes you are commiting.\n");
   write("\tstatus [dir]\tGives you a summary of uncommitted changes you " +
      "have made.\n");
   write("\tpull [dir]\tPulls the latest updates from the external " +
      "repository.\n");
   write("\tpush [dir]\tPushes your commits to the external repository.\n");
   write("\tcommit -m \"Message\" [dir]\tCommit changes you have made back\n" +
      "\t\tto the external repository.\n");
   write("[dir] is optional, and will use the current directory" +
      " if not given.\n");
}

void main(string str) {
   string cmd, dir, arg, message;

   if (!str || str == "") {
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
