inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: extinguish [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Turn off, or extinguish the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\textinguish torch" });
   lines += ({ "\textinguish lamp" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, identify, light, list, listen, look, " +
      "sell, value" });

   this_player()->more(lines);
}

static void main(string str) {
   object obj;

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      write("Extinguish what?\n");
      return;
   }

   if (obj->extinguish()) {
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " extinguishes the " + 
         obj->query_id() + "\n");
      write("You extinguish the " + obj->query_id() + ".\n");
   } else {
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " fumbles around with a " + 
         obj->query_id() + "\n");
   }
}
