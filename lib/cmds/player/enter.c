inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: enter [-h] OBJECT" });
   lines += ({ "" });
   lines += ({ "Allows you to enter the specified object.  To see what you" });
   lines += ({ "can enter, \"look\" around." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tenter hole" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "cast");
   add_also("player", "eat");
   add_also("player", "follow");
   add_also("player", "go");
   add_also("player", "pray");
   add_also("player", "query");
   add_also("player", "quit");
   add_also("player", "wimpy");
}


static void main(string str) {
   string error;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (this_player()->is_resting()) {
      write("You can not do that when your are resting.\n");
      return;
   }

   error = this_environment()->body_exit(this_player(), str);

   if (error) {
      write(error);
   }
}
