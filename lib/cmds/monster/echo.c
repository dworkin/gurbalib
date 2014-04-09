inherit M_COMMAND;

void usage() {
   string *lines;
   object player;

   lines = ({ "Usage: echo [-h] MSG" });
   lines += ({ "Echo the message MSG to the room." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\techo The orc smiles at you." });
   lines += ({ "See also:" });
   lines += ({ "call" });

   player = this_player();
   if (player) {
      player->more(lines);
   }
}

static void main(string str) {
   if (empty_str(str)) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   this_player()->query_environment()->tell_room(this_player(), "\n" +
      str + "\n");
   write("You echo to the room: '" + str + "'.\n");
}
