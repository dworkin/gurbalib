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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "consider");
   add_also("player", "cast");
   add_also("player", "enter");
   add_also("player", "follow");
   add_also("player", "go");
   add_also("player", "pray");
   add_also("player", "quit");
   add_also("player", "wimpy");
}

static void main(string str) {
   object obj;

   if (!alsos) {
      setup_alsos();
   }

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
