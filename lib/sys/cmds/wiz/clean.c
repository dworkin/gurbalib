/* A small command to clear out all the objects in a room - Fudge */

inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: clean [-h]" });
   lines += ({ " " });
   lines += ({ "Clear all the objects out of the current room." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tclean" });
   lines += ({ "See also:" });

   if (query_admin(this_player())) {
      lines += ({ "\tcheck, checkmud, clone, dest, eval, graph, rebuild, " +
         "update, warmboot" });
   } else {
      lines += ({ "\tcheck, clone, dest, eval, graph, rebuild, " +
         "update" });
   }

   return lines;
}

static void main(string arg) {
   object *objs;
   int i;

   if (!empty_str(arg)) {
      this_player()->more(usage());
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
