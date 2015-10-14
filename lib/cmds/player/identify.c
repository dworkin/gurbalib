inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: identify [-h] OBJ" });
   lines += ({ "" });
   lines += ({ "Closely inspect an object OBJ to see if there is any " +
      "addition information." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tidentify sword" });
   lines += ({ "\tidentify helmet" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, extinguish, light, list, listen, look, " +
      "search, sell, value" });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who"
         });
   }

   return lines;
}

static void main(string str) {
   object obj, *wielded;

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      write("Maybe you should get one first?");
      return;
   }

   if (obj->query_detailed_desc()) {
      write(obj->query_detailed_desc());
   } else {
      write("You discover nothing special");
   }
}
