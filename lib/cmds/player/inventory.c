inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: inventory [-h]" });
   lines += ({ "" });
   lines += ({ "Print a list of the items you currently have acquired." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tinventory" });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\thp, junk, levels, score, skills, status, top" });
   } else {
      lines += ({ "\thp, junk, levels, score, skills, top" });
   }

   return lines;
}

static void main(string str) {
   object *inv;
   int i;
   string loc, *lines;

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   inv = this_player()->query_inventory();

   if (sizeof(inv) == 0) {
      write("You are carrying nothing.\n");
   } else {
      lines = ({ "You are carrying:" });
      for (i = 0; i < sizeof(inv); i++) {
         loc = "  " + inv[i]->query_short();
         if (inv[i]->is_wielded() || inv[i]->is_worn()) {
            loc += " %^CYAN%^[" +
               (inv[i]->is_wielded() ? inv[i]->query_wield_position() :
               inv[i]->is_worn() ? inv[i]->query_wear_position() : "") +
               "]%^RESET%^";
         }
         lines += ({ loc });
      }
      this_player()->more(lines, 1);
   }
}
