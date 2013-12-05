inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: attack [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "OBJ offends you, you are going to destroy it." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tattack rat" });
   lines += ({ "See also:" });
   lines += ({ "\tcast, eat, enter, follow, go, pray, wimpy, quit" });

   this_player()->more(lines);
}

static void main(string str) {
   object obj;

   if (!str && (str != "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   obj = this_player()->query_environment()->present(lowercase(str));
   if (!obj) {
      write("Attack what?\n");
      return;
   }

   if (!obj->is_living() || obj->is_dead()) {
      write("You can not attack that.\n");
      return;
   }

   if (obj == this_player()) {
      write("You can not attack yourself.\n");
      return;
   }

   this_player()->targeted_action("$N $vattack $t.", obj);
   this_player()->attack(obj);
}
