inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: halt [-h] "});
   lines += ({ " "});
   lines += ({ "Allows you to stop fighting in the room."});
   lines += ({ " "});
   lines += ({ "Options:"});
   lines += ({ "\t-h\tHelp, this usage message."});
   lines += ({ "Examples:"});
   lines += ({ "\thalt"});
   lines += ({ "See also:"});
   lines += ({ "\tban, forcequit, heal, muzzle, zap"});

   this_player()->more(lines);
}

static void main(string str) {
   int i, was_fight;
   object *obj;

   if (!empty_str(str)) {
      usage();
      return;
   }

   was_fight = 0;
   obj = this_environment()->query_inventory();

   for (i = 0; i < sizeof(obj); i++) {
      if (obj[i]->is_fighting()) {
         was_fight = 1;
         obj[i]->halt_fight();
      }
   }

   if (was_fight) {
      this_player()->write("Combat halted.\n");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " halts combat.\n");
      return;
   }
   this_player()->write("There is no combat here to halt.");
}
