void usage() {
   string *lines;

   lines = ({ "Usage: list [-h]" });
   lines += ({ "" });
   lines += ({ "When in a storage location, allows you to see what you " +
      "have in storage." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlist" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, identify, listen, look, sell, value" });

   this_player()->more(lines);
}

void main(string str) {
   object vendor;
   object *objs;
   int i;

   if (str && str != "") {
      usage();
      return;
   }

   objs = this_environment()->query_inventory();

   for (i = 0; i < sizeof(objs); i++) {
      if (objs[i]->is_vendor())
         vendor = objs[i];
   }
   if (!vendor) {
      write("Perhaps you should try to do this somewhere else?");
      return;
   }

   vendor->do_list(this_player());
}
