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
   lines += ({ "\thp, levels, score, skills" });

   this_player()->more(lines);
}

static void main(string str) {
   object *inv;
   int i;

   if (!empty_str(str)) {
      usage();
      return;
   }

   inv = this_player()->query_inventory();

   if (sizeof(inv) == 0) {
      write("You are carrying nothing.\n");
   } else {
      write("You are carrying:\n");
      for (i = 0; i < sizeof(inv); i++) {
	 if (inv[i]->is_worn()) {
	    write("  " + inv[i]->query_short() +
               " %^CYAN%^[" + inv[i]->query_wear_position() +
               "]%^RESET%^\n");
	 } else if (inv[i]->is_wielded()) {
	    write("  " + inv[i]->query_short() + " %^CYAN%^["
		  + inv[i]->query_wield_position() + "]%^RESET%^\n");
	 } else {
	       write("  " + inv[i]->query_short() + "\n");
	 }
      }
   }
}
