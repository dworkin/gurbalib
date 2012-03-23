void usage() {
   write("Usage: forcequit [-h] PLAYER\n");
   write("Locates the given PLAYER and forces them to quit the game.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   object ob;

   if (!str || (str == "")) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   ob = USER_D->find_player(str);
   if (ob) {
      if (ob->is_player() == 1) {
	 this_player()->simple_action("$N $vforce " + ob->query_name() +
	    " off the game.\n");
	 ob->do_quit();
      }
   } else {
      write("You can't seem to find " + str + ".\n");
   }
}
