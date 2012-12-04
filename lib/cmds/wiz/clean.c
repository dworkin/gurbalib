/* A small command to clear out all the objects in a room
 *
 * Fudge
 */

void usage() {
   string *lines;

   lines = ({ "Usage: clean [-h]\n");
   lines += ({ " " });
   lines += ({ "Clear all the objects out of the current room.\n");
   lines += ({ " " });
   lines += ({ "Options:\n");
   lines += ({ "\t-h\tHelp, this usage message.\n");
   lines += ({ "Examples:" });
   lines += ({ "See also:" });

   if (query_admin(this_player()) {
      lines += ({ "\tcheck, clone, rebuild, update, warmboot" });
   } else {
      lines += ({ "\tcheck, clone, rebuild, update" });
   }

   this_player()->more(lines);
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
