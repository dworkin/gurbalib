inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: list [-h]" });
   lines += ({ "" });
   lines += ({ "When in a storage or shop location, " +
      "allows you to see what shops have on sale, or you have in storage." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlist" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "buy");
   add_also("player", "extinguish");
   add_also("player", "identify");
   add_also("player", "light");
   add_also("player", "listen");
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
   object vendor, *objs;
   int i, maxi;

   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   objs = this_environment()->query_inventory();

   maxi = sizeof(objs);
   for (i = 0; i < maxi; i++) {
      if (objs[i]->is_vendor()) {
         vendor = objs[i];
         continue;
      }
   }
   if (!vendor) {
      write("Perhaps you should try to do this somewhere else?");
      return;
   }

   vendor->do_list(this_player());
}
