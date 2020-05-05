inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: rest [-h]" });
   lines += ({ "" });
   lines += ({ "Sit down so that you are recovering after a battle." });
   lines += ({ "This lets you recover hp and mana " });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\trest" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "consider");
   add_also("player", "cast");
   add_also("player", "stand");
   add_also("player", "score");
   add_also("player", "hp");
}

static void main(string str) {
   string status;

   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   status = this_player()->rest();
   if (status == "sit") {
      write("You sit down to rest.");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() +
         " sits down.");
   } else {
      write("You were already resting, you stand up.");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() +
         " stands up.");
   }
}
