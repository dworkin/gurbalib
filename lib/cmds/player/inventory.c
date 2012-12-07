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

void main(string str) {
   object *inv;
   int i;

   if (str && (str != "")) {
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

	    if (inv[i]->query_adj() != "")
	       write("  " + inv[i]->query_adj() + " " + inv[i]->query_id()
		  + " %^CYAN%^[" + inv[i]->query_wear_position()
		  + "]%^RESET%^\n");
	    else
	       write("  " + inv[i]->query_id() + " %^CYAN%^["
		  + inv[i]->query_wear_position() + "]%^RESET%^\n");

	 } else if (inv[i]->is_wielded()) {
	    if (inv[i]->query_adj() != "")
	       write("  " + inv[i]->query_adj() + " " + inv[i]->query_id()
		  + " %^CYAN%^[" + inv[i]->query_wield_position()
		  + "]%^RESET%^\n");
	    else
	       write("  " + inv[i]->query_id() + " %^CYAN%^["
		  + inv[i]->query_wield_position() + "]%^RESET%^\n");
	 } else {
	    if (inv[i]->query_adj() != "")
	       write("  " + inv[i]->query_adj() + " " + inv[i]->query_id()
		  + "\n");
	    else
	       write("  " + inv[i]->query_id() + "\n");
	 }
      }
   }
}
