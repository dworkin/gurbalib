inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: stand [-h]" });
   lines += ({ "" });
   lines += ({ "Stand up, if you are resting this stops recovering." }); 
   lines += ({ "You are now ready to continue." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tstand" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "cast");
   add_also("player", "rest");
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
      write("You were already standing, you sit down to rest.");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() +
         " sits down.");
   } else {
      write("You you stand up.");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() +
         " stands up.");
   }
}
