void usage() {
   string *lines;

   lines = ({ "Usage: buy [-h] OBJ" });
   lines += ({ "" });
   lines += ({ "Allows you to buy an object OBJ, " +
      "assuming you are near a shop keeper." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tbuy sword" });
   lines += ({ "\tbuy helmet" });
   lines += ({ "See also:" });
   lines += ({ "\tidentify, list, look, retrieve, sell, store, value" });

   this_player()->more(lines);
}

/* Created by Fudge */

void main(string str) {
   object *objs;
   int i;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   objs = this_environment()->query_inventory();
   for (i = 0; i < sizeof(objs); i++) {
      if (objs[i]->is_vendor() == 1) {
	 /* Found the shopkeeper */

	 objs[i]->do_sell(this_player(), str);
	 return;

      }
   }

   write("Buy from whom?");
}
