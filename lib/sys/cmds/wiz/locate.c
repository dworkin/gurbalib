inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: locate [-h] PLAYER" });
   lines += ({ " " });
   lines += ({ "Locate player PLAYER through intermud." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlocate sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "look");
   add_also("player", "who");

   add_also("wiz", "last");
   add_also("wiz", "mudlist");
   add_also("wiz", "possess");
   add_also("wiz", "rwho");
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

   IMUD_D->do_locate(str);
}
