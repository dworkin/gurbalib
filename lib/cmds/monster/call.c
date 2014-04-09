inherit M_COMMAND;

void usage() {
   string *lines;
   object player;

   lines = ({ "Usage: call [-h] FUNCTION [ARGS]" });
   lines += ({ "call the function FUNCTION with arguments ARGS in this " +
      "object." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcall set_gender male" });
   lines += ({ "See also:" });
   lines += ({ "echo" });

   player = this_player();
   if (player) {
      player->more(lines);
   }
}

static void main(string arg) {
   string *tmp;
   int i;

   if (empty_str(arg)) {
      usage();
      return;
   }
   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   tmp = explode(arg, " ");
   call_other(this_player(), tmp...);
}
