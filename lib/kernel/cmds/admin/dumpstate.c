void usage() {
   string *lines;

   lines = ({ "Usage: dumpstate [-h]" });
   lines += ({ "Create a backup of the current state of the mud." });
   lines += ({ "* Note:" });
   lines += ({ "* The statedump is made when the current thread ends." });
   lines += ({ "* We schedule a 0 delay call_out which will run after" });
   lines += ({ "* the current thread ends to notify the user." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdumpstate" });
   lines += ({ "See also: clone, rebuild, shutdown, update, warmboot" });

   this_player()->more(lines);
}

void main(string str) {
   if (str && str != "") {
      usage();
      return;
   }

   if (!require_priv("system")) {
      write("You must be admin to do that.");
      return;
   }

   DRIVER->save_game();
   write("Writing statedump");
   call_out("done", 0);
}

void done() {
   write("Statedump done.");
}
