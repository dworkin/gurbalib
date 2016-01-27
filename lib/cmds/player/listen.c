inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: listen [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Listen to the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlisten door" });
   lines += ({ "\tlisten" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "buy");
   add_also("player", "extinguish");
   add_also("player", "identify");
   add_also("player", "light");
   add_also("player", "list");
   add_also("player", "look");
   add_also("player", "search");
   add_also("player", "sell");
   add_also("player", "value");

   add_also("wiz", "last");
   add_also("wiz", "locate");
   add_also("wiz", "mudlist");
   add_also("wiz", "possess");
   add_also("wiz", "rwho");
   add_also("wiz", "snoop");
   add_also("wiz", "where");
   add_also("wiz", "who");
}

static void main(string str) {
   object obj;

   if (!alsos) {
      setup_alsos();
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (!str || str == "" || strcmp(str, "room") == 0) {
      obj = this_player()->query_environment();
   } else {
      obj = this_player()->present(str);
      if (!obj) {
         obj = this_player()->query_environment()->present(str);
      }
   }

   if (!obj) {
      write("Listen to what?\n");
      return;
   }

   if (!call_other(obj, "do_listen")) {
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " Pauses to listens to " + 
         obj->query_id() + "\n");
      write("You hear nothing.\n");
   }
}
