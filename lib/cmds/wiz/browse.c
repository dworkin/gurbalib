void usage() {
   string *lines;
   lines = ({ "Usage: browse [-h] [dir]" });
   lines += ({ " " });
   lines += ({ "An interactive way to look at files." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "See also:" });
   lines += ({ "\tcd, edit, ls, pwd" });

   this_player()->more(lines);
}

void main(varargs string arg) {
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   "/sys/obj/browser"->browse(arg);
}
