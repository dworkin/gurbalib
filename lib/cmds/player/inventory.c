inherit M_COMMAND;

void usage() {
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
   lines += ({ "\thp, junk, levels, score, skills" });

   this_player()->more(lines);
}

static void main(string str) {
   object *inv;
   int i;
	string *lines;
	string loc;

   if (!empty_str(str)) {
      usage();
      return;
   }

   inv = this_player()->query_inventory();
	lines = ({ });

   if (sizeof(inv) == 0) {
      write("You are carrying nothing.\n");
   } else {
      lines += ({ "You are carrying:\n" });
      for (i = 0; i < sizeof(inv); i++) {
			loc = "  " + inv[i]->query_short();
			if (inv[i]->is_wielded() || inv[i]->is_worn()) {
				loc += " %^CYAN%^[" +
					(inv[i]->is_wielded() ? inv[i]->query_wield_position() :
					inv[i]->is_worn() ? inv[i]->query_wear_position() : "") +
					"]%^RESET%^\n";
			}
			lines += ({ loc });
		}
		this_player()->more(lines, 1);
	}
}
