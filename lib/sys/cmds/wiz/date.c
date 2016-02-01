inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: date [-h]" });
   lines += ({ " " });
   lines += ({ "Show the real world time and date." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdate" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "scan");
   add_also("wiz", "status");
   add_also("wiz", "time");
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   write(ctime(time()) + "\n");
}
