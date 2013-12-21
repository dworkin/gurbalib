inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: list [-h]" });
   lines += ({ "" });
   lines += ({ "When in a storage or shop location, " +
      "allows you to see what shops have on sale, or you have in storage." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlist" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, extinguish, identify, light, listen, look, " +
      "sell, value" });

   this_player()->more(lines);
}

static void main(string str) {
   object vendor;
   object *objs;
   int i, maxi;

   if (!empty_str(str)) {
      usage();
      return;
   }

   objs = this_environment()->query_inventory();

   maxi = sizeof(objs);
   for (i = 0; i < maxi; i++) {
      if (objs[i]->is_vendor()) {
         vendor = objs[i];
         continue;
      }
   }
   if (!vendor) {
      write("Perhaps you should try to do this somewhere else?");
      return;
   }

   vendor->do_list(this_player());
}
