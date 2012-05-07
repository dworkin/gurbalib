void usage() {
   write("Usage compose [-h]");
   write("Scan the objects in your inventory and create an autoload string.\n");
   write("So those objects will be loaded next time you login.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: aload\n");
}

void main(string str) {
   object ob;
   string tmp;
   object *inv;
   int i, max;

   if (str != "") {
      usage();
      return;
   }
   inv = this_player()->query_inventory();
   max = sizeof(inv);
write("inventory is size: " + max + "\n");
   for (i = 0; i < max; i++) {
      tmp = inv[i]->query_autoload_filename();
      if (tmp && (tmp != "")) {
write("Adding : " + tmp + "\n");
         str = str + tmp + "^!";
      }
   }

   /* terminate autoload string */
   str = str + "*^!";
   write("compose_autoload_string = " + str + "\n");
   this_player()->set_autoload_string(str);
}
