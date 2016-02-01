inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: last [-h] [player]" });
   lines += ({ " " });
   lines += ({ "Find out when a player was last logged in." });
   lines += ({ "If no player is given show last for everyone." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlast" });
   lines += ({ "\tlast sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "look");
   add_also("player", "who");

   add_also("wiz", "locate");
   add_also("wiz", "mudlist");
   add_also("wiz", "possess");
   add_also("wiz", "rwho");
   add_also("wiz", "snoop");
   add_also("wiz", "where");
}

static void main(string str) {
   string msg;

   if (!alsos) {
      setup_alsos();
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (!require_priv("system")) {
      write("Access denied");
      return;
   }

   if (str != "") {
      msg = LAST_D->query_entry(lowercase(str));
   } else {
      msg = LAST_D->query_list();
   }
   write(msg);
}
