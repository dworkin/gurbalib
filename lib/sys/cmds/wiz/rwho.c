inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: rwho [-h] MUDNAME" });
   lines += ({ " " });
   lines += ({ "Remote who, lists users on another mud." });
   lines += ({ "To see what other muds you can look at use the command: " +
      "mudlist" });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\t rwho gurbalib" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "look");
   add_also("player", "who");

   add_also("wiz", "last");
   add_also("wiz", "locate");
   add_also("wiz", "mudlist");
   add_also("wiz", "possess");
   add_also("wiz", "snoop");
   add_also("wiz", "where");
}

static void main(string str) {
   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   IMUD_D->do_who(str);
}
