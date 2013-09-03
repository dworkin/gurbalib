inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: close [-h] [all|OBJ]" });
   lines += ({ "" });
   lines += ({ "Allows you to close a given object OBJ." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tClose everything you can." });
   lines += ({ "Examples:" });
   lines += ({ "\tclose chest" });
   lines += ({ "See also:" });
   lines += ({ "\topen" });

   this_player()->more(lines);
}

static void do_close(object obj, int loud) {
   string slot;
   object worn;

   if (!obj) {
      if (loud) {
         write("what are you trying to close?");
      }
      return;
   }

   if (!obj->is_closable()) {
      if (loud) {
         write("You can't close the " + obj->query_id() + ".");
      }
      return;
   }
   obj->do_close(this_player());
}

static void main(string str) {
   object obj;
   object *inv;
   int i, max;

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }
   str = lowercase(str);

   if (str == "all") {
      inv = this_player()->query_environment()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_close(inv[i],0);
      }

      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_close(inv[i],0);
      }
      return;
   }

   obj = this_player()->query_environment();
   if (obj->do_close(str)) {
      return;
   }

   obj = this_player()->present(str);
   if (!obj) {
      obj = this_player()->query_environment()->present(str);
   }
   do_close(obj,1);
}
