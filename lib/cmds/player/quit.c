inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines =({ "Usage: quit [-h] [-r]" });
   lines += ({ "" });
   lines += ({ "This is how you leave the game." });
   lines += ({ "Note: You will keep your money, but you will drop all " +
      "of your items " });
   lines += ({ "when you quit." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-r\tRemove your account.  WARNING this is not reversible." });
   lines += ({ "Examples:" });
   lines += ({ "\tquit" });
   lines += ({ "\tquit -r" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, cast, eat, enter, follow, go, pray, wimpy" });
   this_player()->more(lines);
}

void verify_remove(string str) {
   if (str == "Y" || str == "y") {
      USER_D->delete_user(this_player()->query_name());
   } else {
      write("Removal cancelled.\n");
   }
}

static void main(string str) {
   if (!empty_str(str)) {
      if (str == "-r") {
         write("WARNING!!! this is not reversible.\n");
         write("Are you sure you really want to remove your player? (Y|N)\n");
         this_player()->input_to_object(this_object(), "verify_remove");
         return;
      }
      usage();
      return;
   }

   this_player()->do_quit();
}
