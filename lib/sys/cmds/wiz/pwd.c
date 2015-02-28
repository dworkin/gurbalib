inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: pwd [-h]" });
   lines += ({ " " });
   lines += ({ "Prints the current working directory." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpwd" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, cp, diff, edit, indent, ls, more, mkdir, " +
      "rm, tail" });

   this_player()->more(lines);
}

static void main(string str) {

   if (!empty_str(str)) {
      usage();
   } else {
      write("%^BOLD%^" + this_player()->query_env("cwd") + "%^RESET%^\n");
   }
}
