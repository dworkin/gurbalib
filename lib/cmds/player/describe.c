inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: describe [-h] [DESCRIPTION]" });
   lines += ({ "" });
   lines += ({ "Allows you to change your DESCRIPTION, so that when someone " +
      "looks at you," });
   lines += ({ "They know what you look like." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdescribe The unassuming little elf." });
   lines += ({ "See also:" });
   lines += ({ "\talias, ansi, chfn, clear, ignore, passwd" });

   if (query_admin(this_player())) {
      lines += ({ "\tcoloradm" });
   }

   this_player()->more(lines);
}

static void main(string str) {

   if (empty_str(str)) {
      write("Your current description:\n   " + this_player()->query_long() +
         "\n");
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (str) {
      str = replace_string(str, "$N", this_player()->query_Name());
   }

   this_player()->set_long(str);
   this_player()->simple_action("$N $vchange $p looks.");
}
