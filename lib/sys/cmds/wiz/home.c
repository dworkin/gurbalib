inherit M_COMMAND;
void usage() {
   string *lines;

   lines = ({ "Usage: home [-h]" });
   lines += ({ " " });
   lines += ({ "Transport you to your \"work room\"." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\thome" });
   lines += ({ "See also:" });
   lines += ({ "\tgoto, summon, where" });

   this_player()->more(lines);
}

static void main(string str) {

   string error, name;
   object env;
   string filename;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (str && (str != "")) {
      usage();
      return;
   }

   name = this_player()->query_name();

   filename = WIZ_DIR + "/" + name + "/rooms/workroom";

   if (!file_exists(filename + ".c")) {
      filename = WIZ_DIR + "/" + name + "/workroom";

      if (file_exists(filename + ".c")) {
	 if (file_exists(WIZ_DIR + "/" + name + "/rooms") == 0) {
	    write("Please create a " + WIZ_DIR + "/" + name +
	       "/rooms directory and " + "move your workroom into it.");
	 } else {
	    write("Please move your workroom into " + WIZ_DIR + "/" + name +
	       "/rooms/");
	 }
      }
   }

   if (!file_exists(filename + ".c")) {
      write("Make one first.\n");
      return;
   }

   env = this_player()->query_environment();

   this_player()->simple_action("$N $vgo home.");
   this_player()->move(filename);
   if (!error) {
      this_player()->do_look(0);
   } else {
      env->tell_room(this_player(),
	 this_player()->query_Name() + " looks confused.");
      write("You can't go home.\nError: " + error);
   }
}
