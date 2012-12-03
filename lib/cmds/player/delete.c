void usage() {
   write("Usage: delete [-h] #\n");
   write("Allows you to remove posts from a message board.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\tdelete 3\n");
   write("See also: look, post, read\n");
}

void main(string str) {
   object ob;
   string *lines;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   ob = this_environment()->present("board");
   if (!ob) {
      write("Try reading a message at a message board.\n");
      return;
   }

   if (!str || str == "") {
      write("Read what?");
      return;
   }

   if (ob->query_msg_exists(str) == 1) {
      ob->remove_message(str);
   } else {
      write("No such message.\n");
   }
   return;
}
