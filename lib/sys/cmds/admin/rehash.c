inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: rehash [-h]" });
   lines += ({ " " });
   lines += ({ "Re evaluate the command paths to add/remove commands." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\trehash" });
   lines += ({ "See also:" });
   lines += ({ "\tXXX copy cmdadm usage and add this one to related ones" });

   this_player()->more(lines);
}

static void main(string str) {
   if (str && str != "") {
      usage();
   } else {
      COMMAND_D->rehash();
      write("Ok.\n"); /* Would be nice for rehash to return # of commands or
        something similar to print out for feedback XXX */
   }
}
