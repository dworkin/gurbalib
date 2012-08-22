void usage() {
   write("Usage: page [-h] CMD\n");
   write("Ask your page to do command CMD.\n");
   write("If no page is present, summon one.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

/* moved this from fighters guild specific command.  Need to convert it to
   a skill and give the skill to fighters...
*/

void main(string str) {
   object ob;

   string page;

   page = this_player()->query_name() + "s page";
   ob = this_player()->query_environment()->present(page);

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (ob) {
      ob->parse(str);
   } else {
      ob = clone_object("/std/page.c");
      if (ob) {
	 ob->move(this_player()->query_environment());
	 ob->set_master(this_player());
	 ob->setup();
	 this_player()->simple_action("$N $vyell for $p page.");
      } else {
	 this_player()->simple_action("$N $vyell for $p page, " +
            "but he can't be yelling loud enough.");
      }
   }
}
