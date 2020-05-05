inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: go [-h] DIRECTION" });
   lines += ({ "" });
   lines += ({ "Allows you to move in the specified direction.  To see " +
      "where you" });
   lines += ({ "can go, \"look\" around." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tgo north" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "consider");
   add_also("player", "cast");
   add_also("player", "eat");
   add_also("player", "enter");
   add_also("player", "follow");
   add_also("player", "pray");
   add_also("player", "quit");
   add_also("player", "wimpy");
}

static void main(string str) {
   string error, str2;
   int len;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(str, "-%s", str) || sscanf(str, "%s -%s", str, str2)) {
      this_player()->more(usage());
      return;
   }

   if (this_player()->is_resting()) {
      write("You can not do that when your are resting.\n");
      return;
   }

   len = strlen(str);
   if (str[len - 1] == ' ') {
      str = str[..len - 2];
   }

   error = this_environment()->body_exit(this_player(), str);

   if (error) {
      write(error);
   }
}
