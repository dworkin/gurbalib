inherit M_COMMAND;

string *usage(void) {
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

   return lines;
}

void done(void) {
   write("Statedump done.");
}

static void main(string str) {
   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   DRIVER->save_game();
   write("Writing statedump");
   call_out("done", 0);
}
