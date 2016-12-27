inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: dumpstate [-h]" });
   lines += ({ "" });
   lines += ({ "Create a backup of the current state of the mud." });
   lines += ({ "Note:" });
   lines += ({ "\tThe statedump is made when the current thread ends." });
   lines += ({ "\tWe schedule a 0 delay call_out which will run after" });
   lines += ({ "\tthe current thread ends to notify the user." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdumpstate" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "check");
   add_also("wiz", "clean");
   add_also("wiz", "clone");
   add_also("wiz", "dest");
   add_also("wiz", "eval");
   add_also("wiz", "update");

   add_also("admin", "rebuild");
   add_also("admin", "shutdown");
   add_also("admin", "warmboot");
}

void done(void) {
   write("Statedump done.");
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   DRIVER->save_game();
   write("Writing statedump");
   call_out("done", 0);
}
