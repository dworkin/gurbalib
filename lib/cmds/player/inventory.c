void usage() {
   write("Usage: inventory [-h]\n");
   write("Print a list of the items you currently have acquired.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
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
