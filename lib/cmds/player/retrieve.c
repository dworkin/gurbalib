void usage() {
   write("Usage: retrieve [-h] OBJ\n");
   write("Allows you to retrieve an object OBJ, from storage.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\tretrieve sword\n");
   write("\tretrieve helmet\n");
   write("See also: buy, identify, list, look, sell, store, value\n");
}

void main(string str) {

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (!this_environment()->is_storage()) {
      this_player()->write("Perhaps you should try retrieving your item from " +
	 "a storage location?\n");
      return;
   }

   this_environment()->borrow_object(str);
}
