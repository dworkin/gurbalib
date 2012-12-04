void usage() {
   string *lines;

   lines = ({ "Usage: delete [-h] #" });
   lines += ({ "" });
   lines += ({ "Allows you to remove posts from a message board." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tdelete 3" });
   lines += ({ "See also:" });
   lines += ({ "\tlook, post, read" });

   this_player()->more(lines);
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
