void usage() {
   write("Usage: aload [-h] [save]\n");
   write("If no arguments are given, load your current autoload objects.\n");
   write("If save is specified, create an autoload string from your " +
      "inventory.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: compose\n");
}

void main(string str) {
   string file, action, rest;
   object ob;
   object *inv;
   int i, max;

   if (str && str != "") {
      if (str == "save") {
         this_player()->compose_autoload_string();
         str = this_player()->query_autoload_string();
         write("Autoload string set to: " + str + "\n");
      } else {
         usage();
         return;
      }
   }

   this_player()->clone_autoload_objects();
}
