inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: eat [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Consume the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\teat apple" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, cast, enter, follow, go, pray, query, quit, wimpy" });

   return lines;
}

static void main(string str) {
   object obj;

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      write("Consume what?\n");
      return;
   }

   if (!obj->is_eatable()) {
      write(" You can not consume that.\n");
      return;
   }

   call_other(obj, "do_eat");
}
