inherit M_COMMAND;

void usage(void) {
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
   lines += ({ "\tlook, mail, post, read" });

   this_player()->more(lines);
}

static void main(string str) {
   object ob;
   string *lines;

   if (empty_str(str)) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   ob = this_environment()->present("board");
   if (!ob) {
      write("You need to be at a message board to delete items.\n");
      return;
   }

   if (!str || (str == "")) {
      write("Delete what?");
      return;
   }

   if (ob->query_msg_exists(str) == 1) {
      ob->remove_message(str);
   } else {
      write("No such message.\n");
   }
   return;
}
