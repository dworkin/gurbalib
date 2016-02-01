inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: browse [-h] [dir]" });
   lines += ({ " " });
   lines += ({ "An interactive way to look at files." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tbrowse void.c" });
   lines += ({ "\tbrowse " + DOMAINS_DIR + "/required/rooms" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "cat");
   add_also("wiz", "cd");
   add_also("wiz", "cp");
   add_also("wiz", "diff");
   add_also("wiz", "edit");
   add_also("wiz", "indent");
   add_also("wiz", "ls");
   add_also("wiz", "more");
   add_also("wiz", "mkdir");
   add_also("wiz", "pwd");
   add_also("wiz", "rm");
   add_also("wiz", "tail");
}

static void main(string arg) {
   if (!alsos) {
      setup_alsos();
   }

   if (arg && sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
      return;
   }

   "/sys/obj/browser"->browse(arg);
}
