/* A small command to clear out all the objects in a room
 *
 * Fudge
 */

void usage() {
   write("Usage: clean [-h]\n");
   write("Clear all the objects out of the current room.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string arg) {
   object *objs;
   int i;

   if (arg && arg != "") {
      usage();
      return;
   }

   objs = this_environment()->query_inventory();
   for (i = 0; i < sizeof(objs); i++) {
      if (!objs[i]->is_player()) {
	 objs[i]->destruct();
      }
   }
   this_player()->simple_action("$N $vclean the room.", nil);
}
