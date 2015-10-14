inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: call [-h] FUNCTION [ARGS]" });
   lines += ({ "call the function FUNCTION with arguments ARGS in this " +
      "object." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcall set_gender male" });
   lines += ({ "See also:" });
   lines += ({ "\techo" });

   return lines;
}

static void main(string arg) {
   string *tmp;
   int i;
   object player;

   if (empty_str(arg)) {
      player = this_player();
      if (player) {
         player->more(usage());
      }
      return;
   }
   if (sscanf(arg, "-%s", arg)) {
      player = this_player();
      if (player) {
         player->more(usage());
      }
      return;
   }

   tmp = explode(arg, " ");
   call_other(this_player(), tmp...);
}
