inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: echo [-h] MSG" });
   lines += ({ "Echo the message MSG to the room." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\techo The orc smiles at you." });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("monster", "call");
}

static void main(string str) {
   object player;

   if (empty_str(str)) {
      player = this_player();
      if (player) {
         player->more(usage());
      }
      return;
   }
   if (sscanf(str, "-%s", str)) {
      player = this_player();
      if (player) {
         player->more(usage());
      }
      return;
   }

   this_player()->query_environment()->tell_room(this_player(), "\n" +
      str + "\n");
   write("You echo to the room: '" + str + "'.\n");
}
