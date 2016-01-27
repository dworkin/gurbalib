inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: open [-h] [all|OBJ]" });
   lines += ({ "" });
   lines += ({ "Allows you to open a given object OBJ." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tOpen everything you can." });
   lines += ({ "Examples:" });
   lines += ({ "\topen chest" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "close");
}

static void do_open(object obj, int loud) {
   string slot;
   object worn;

   if (!obj) {
         if (loud) { 
         write("what are you trying to open?");
      }
      return;
   }

   if (!obj->is_openable()) {
      if (loud) {
         write("You can't open the " + obj->query_id() + ".");
      }
      return;
   }
   obj->do_open(this_player());
}

static void main(string str) {
   object obj, *inv;
   int i, max;

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

   str = lowercase(str);

   if (str == "all") {
      inv = this_player()->query_environment()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_open(inv[i], 0);
      }

      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_open(inv[i], 0);
      }
      return;
   }

   obj = this_player()->query_environment();
   if (obj->do_open(str)) {
      return;
   }

   obj = this_player()->present(str);
   if (!obj) {
      obj = this_player()->query_environment()->present(str);
   }
   do_open(obj, 1);
}
