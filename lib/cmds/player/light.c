inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: light [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Turn on, or light the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlight torch" });
   lines += ({ "\tlight lamp" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, extinguish, identify, list, listen, look, " +
      "sell, value" });

   this_player()->more(lines);
}

static void main(string str) {
   object obj;

   if (empty_str(str)) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      write("Light what?\n");
      return;
   }

   if (obj->light()) {
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " lights " + 
         obj->query_id() + "\n");
      write("You light the " + obj->query_id() + ".\n");
   } else {
      write("That isn't lightable.\n");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " fumbles around with a " + 
         obj->query_id() + "\n");
   }
}
