void usage() {
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
   lines += ({ "See also:" });
   lines += ({ "\tclose" });

   this_player()->more(lines);
}

void do_open(object obj, int loud) {
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

void main(string str) {
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

   if (str == "all") {
      inv = this_player()->query_environment()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_open(inv[i],0);
      }

      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_open(inv[i],0);
      }
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      obj = this_player()->query_environment()->present(lowercase(str));
   }
   do_open(obj,1);
}
