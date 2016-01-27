inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: query [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Sizeup OBJ, and see how you measure up to them." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tquery rat" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "cast");
   add_also("player", "eat");
   add_also("player", "enter");
   add_also("player", "follow");
   add_also("player", "go");
   add_also("player", "pray");
   add_also("player", "quit");
   add_also("player", "wimpy");
}

static void main(string str) {
   object obj;
   float x, y;
   string name;

   if (!alsos) {
      setup_alsos();
   }

   if (!str && (str != "")) {
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

   obj = this_player()->query_environment()->present(lowercase(str));
   if (!obj) {
      write("Query what?\n");
      return;
   }

   if (!obj->is_living() || obj->is_dead()) {
      write("You can not query that.\n");
      return;
   }

   if (obj == this_player()) {
      write("You are a bit disapointing.\n");
      return;
   }

   name = obj->query_short();
   write("You look long and hard at " + name + "\n");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " sizes up " + name + ".\n");

   y = (float)obj->query_max_hp();
   x = (float)this_player()->query_max_hp();
   write(name + " is a thread level " + (y / x) + " to you.\n");
}
