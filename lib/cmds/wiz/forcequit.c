void usage() {
   string *lines;

   lines = ({ "Usage: forcequit [-h] PLAYER" });
   lines += ({ " " });
   lines += ({ "Locates the given PLAYER and forces them to quit the game." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tforcequit sirdude" });
   lines += ({ "See also:" });
   lines += ({ "\tban, halt, heal, muzzle, zap" });

   this_player()->more(lines);
}

void main(string str) {
   object ob;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

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
