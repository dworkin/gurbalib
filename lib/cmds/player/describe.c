inherit M_COMMAND;

string *usage(void) {
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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "alias");
   add_also("player", "ansi");
   add_also("player", "clear");
   add_also("player", "ignore");
   add_also("player", "passwd");

   add_also("admin", "coloradm");
}

static void main(string str) {

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      write("Your current description:\n   " + this_player()->query_long() +
         "\n");
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (str) {
      str = replace_string(str, "$N", this_player()->query_Name());
   }

   this_player()->set_long(str);
   this_player()->simple_action("$N $vchange $p looks.");
}
