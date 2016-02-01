inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: pwd [-h]" });
   lines += ({ " " });
   lines += ({ "Prints the current working directory." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpwd" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "browse");
   add_also("wiz", "cat");
   add_also("wiz", "cd");
   add_also("wiz", "cp");
   add_also("wiz", "diff");
   add_also("wiz", "edit");
   add_also("wiz", "indent");
   add_also("wiz", "ls");
   add_also("wiz", "more");
   add_also("wiz", "mkdir");
   add_also("wiz", "rm");
   add_also("wiz", "tail");
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
   } else {
      write("%^BOLD%^" + this_player()->query_env("cwd") + "%^RESET%^\n");
   }
}
