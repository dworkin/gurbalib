inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: dumpstate [-h]" });
   lines += ({ "" });
   lines += ({ "Create a backup of the current state of the mud." });
   lines += ({ "* Note:" });
   lines += ({ "* The statedump is made when the current thread ends." });
   lines += ({ "* We schedule a 0 delay call_out which will run after" });
   lines += ({ "* the current thread ends to notify the user." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdumpstate" });
   lines += ({ "See also:" });
   lines += ({ "\tcheck, clean, clone, dest, eval, rebuild, " +
      "shutdown, update, warmboot" });

   this_player()->more(lines);
}

void done() {
   write("Statedump done.");
}

static void main(string str) {
   if (!empty_str(str)) {
      usage();
      return;
   }

   DRIVER->save_game();
   write("Writing statedump");
   call_out("done", 0);
}
