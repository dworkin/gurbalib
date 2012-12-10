void usage() {
   string *lines;
   lines = ({ "Usage: browse [-h] [dir]" });
   lines += ({ " " });
   lines += ({ "An interactive way to look at files." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tbrowse void.c" });
   lines += ({ "\tbrowse /domains/required/rooms" });
   lines += ({ "See also:" });
   lines += ({ "\tcat, cd, cp, diff, edit, ls, more, mkdir, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

void main(varargs string arg) {
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   "/sys/obj/browser"->browse(arg);
}
