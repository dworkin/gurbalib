void usage() {
   write("Usage: buy [-h] OBJ\n");
   write("Allows you to buy an object OBJ, " +
      "assuming you are near a shop keeper.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("buy sword\n");
   write("buy helmet\n");
   write("See also: sell, retrieve, store\n");
}

/* Created by Fudge */

void main(string str) {
   object *objs;
   int i;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   objs = this_environment()->query_inventory();
   for (i = 0; i < sizeof(objs); i++) {
      if (objs[i]->is_vendor() == 1) {
	 /* Found the shopkeeper */

	 objs[i]->do_sell(this_player(), str);
	 return;

      }
   }

   write("Buy from whom?");
}
