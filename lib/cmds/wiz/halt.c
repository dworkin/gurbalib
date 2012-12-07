void usage() {
   write("Usage: halt [-h] \n");
   write("Allows you to stop fighting in the room.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   int i;
   object *obj;

   if (str && str != "") {
      usage();
      return;
   }

   obj = this_environment()->query_inventory();

   for (i = 0; i < sizeof(obj); i++) {
      if (obj[i]->is_fighting())
	 obj[i]->halt_fight();
   }
   this_player()->write("Combat halted.\n");
}
