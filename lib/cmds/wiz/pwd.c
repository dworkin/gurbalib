void usage() {
   string *lines;

   lines += ({ "Usage: pwd [-h]" });
   lines += ({ " " });
   lines += ({ "Prints the current working directory." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpwd" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, diff, edit, ls, more, mkdir, rm, tail" });

   this_player()->more(lines);
}

void main(string str) {
   if (str && (str != "")) {
      usage();
   } else {
      write("%^BOLD%^" + this_player()->query_env("pwd") + "%^RESET%^\n");
   }
}
