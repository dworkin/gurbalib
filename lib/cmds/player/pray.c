inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: pray [-h] [prayer]" });
   lines += ({ "" });
   lines += ({ "Allows you to regain your body...." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpray for forgiveness" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "consider");
   add_also("player", "cast");
   add_also("player", "eat");
   add_also("player", "enter");
   add_also("player", "follow");
   add_also("player", "go");
   add_also("player", "quit");
   add_also("player", "wimpy");
}

static void main(string str) {
   object obj;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      write("You pray.\n");
      this_player()->query_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " prays.\n");
   } else if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   } else {
      switch (str[strlen(str) - 1]) {
         case '.':
         case '?':
         case '!':
         case ',':
            break;
         default:
            str += ".";
            break;
      }

      write("You pray: " + str + "\n");
      this_player()->query_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " prays: " + str + "\n");
   }

   if (this_player()->is_dead()) {
      write("You feel a shimmering light warm your entire body.");
      this_player()->query_environment()->tell_room(this_player(), 
         "A shimmering light envelopes " + this_player()->query_Name() + ".");
      this_player()->set_hp(1);
      this_player()->set_dead(0);
   }
}
