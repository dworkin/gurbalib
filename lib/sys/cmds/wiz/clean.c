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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "check");
   add_also("wiz", "clone");
   add_also("wiz", "dest");
   add_also("wiz", "eval");
   add_also("wiz", "graph");
   add_also("wiz", "rebuild");
   add_also("wiz", "update");

   add_also("admin", "checkmud");
   add_also("admin", "warmboot");
}

static void main(string arg) {
   object *objs;
   int i;

   if (!alsos) {
      setup_alsos();
   }

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
