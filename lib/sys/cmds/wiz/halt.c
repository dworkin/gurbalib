inherit M_COMMAND;
void usage() {
   string *lines;

   lines = ({ "Usage: halt [-h] " });
   lines += ({ " " });
   lines += ({ "Allows you to stop fighting in the room." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\thalt" });
   lines += ({ "See also:" });
   lines += ({ "\tban, forcequit, heal, muzzle, zap" });

   this_player()->more(lines);
}

static void main(string str) {
   int i;
   object *obj;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (str && (str != "")) {
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
