inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: search [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Search the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tsearch junk" });
   lines += ({ "\tsearch" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, extinguish, identify, light, list, listen, look, " +
      "sell, value" });
   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who" 
      });
   }

   this_player()->more(lines);
}

static void main(string str) {
   object obj;

   if (this_environment()->is_dark()) {
      if (query_wizard(this_player())) {
         write("This room is dark, however, being a wizard allows " +
            "you to see in the dark.\n");
      } else if (this_player()->query_race_object()->has_darkvision()) {
         write("This room is dark, however, your race allows " +
            "you to see in the dark.\n");
      } else {
         write("It is too dark to see.\n");
         return;
      }
   }

   if (empty_str(str)) {
      if (!call_other(this_player()->query_environment(), "functionp", 
         "do_search")) {
         this_player()->query_environment()->tell_room(this_player(),
           this_player()->query_Name() + "Meticulously searches the room.\n");
         write("You find nothing.\n");
      } else {
         call_other(this_player()->query_environment(),"do_search","");
      }
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      obj = this_player()->query_environment()->present(lowercase(str));
   }
   if (!obj) {
      write("Search what?\n");
      return;
   }

   if (obj->is_living()) {
      write("Thats not acceptable behavior.");
      return;
   }

   if (!call_other(obj,"functionp","do_search")) {
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " searches " + 
         obj->query_id() + "\n");
      write("You find nothing.\n");
   } else {
      call_other(obj,"do_search", "");
   }
}
