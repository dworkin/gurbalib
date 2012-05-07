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
   string file, argument, rest;
   object ob;
   object *inv;
   int i, max;

   if (str && str != "") {
      if (str == "save") {
         str = "";
         inv = this_player()->query_inventory();
         max = sizeof(inv);
         for (i = 0; i < max; i++) {
            file = inv[i]->query_autoload_filename();
            if (file && (file != "")) {
               str = str + file + "^!";
            }
         }

         /* terminate autoload string */
         str = str + "*^!";
         write("compose_autoload_string = " + str + "\n");
         this_player()->set_autoload_string(str);
         return;
      } else {
         usage();
         return;
      }
   }

   str = this_player()->query_autoload_string();

   while (str && str != "*^!") {
      if (sscanf(str, "%s^!%s", file, rest) != 2) {
	 write("Autoload string corrupt.\n");
         write("Values file: " + file + "\n");
         write("Values rest: " + rest + "\n");
	 return;
      }
      str = rest;
      if (file_exists(file)) {
	 write("file = " + file + "\n");
	 write("rest = " + rest + "\n\n");
	 ob = clone_object(file);
	 if (ob) {
	    ob->move(this_player()->query_environment());
	    ob->setup();
	    ob->move(this_player());
	 }
      }
   }
}
