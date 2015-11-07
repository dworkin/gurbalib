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
   lines += ({ "See also:" });
   lines += ({ "\tbuy, extinguish, identify, light, list, look, " +
      "search, sell, value" });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who" 
         });
   }

   return lines;
}

static void main(string str) {
   object obj;

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
