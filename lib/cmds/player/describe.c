void usage() {
   string *lines;

   lines = ({ "Usage: describe [-h] DESCRIPTION" });
   lines += ({ "Allows you to change your DESCRIPTION, so that when someone " +
      "looks at you," });
   lines += ({ "They know what you look like." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdescribe The unassuming little elf." });
   lines += ({ "See also: chfn, passwd" });

   this_player()->more(lines);
}

void main(string str) {

   if (!str || str == "") {
      usage();
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
