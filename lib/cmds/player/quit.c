void usage() {
   string *lines;

   lines =({ "Usage: quit [-h] [-r]" });
   lines += ({ "" });
   lines += ({ "This is how you leave the game." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-r\tRemove your account.  WARNING this is not reversable." });
   lines += ({ "Examples:" });
   lines += ({ "\tquit" });
   lines += ({ "\tquit -r" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, cast, eat, enter, follow, go, pray" });


   this_player()->more(lines);
}

void verify_remove(string str) {
   if (str == "Y" || str == "y") {
      /* XXX Need to deal with security issues and remove mail and wizdir if
	 they exist */
      USER_D->delete_user(this_player()->query_name());
      /* this_player()->do_quit(); */
   } else {
      write("Removal cancelled.\n");
   }
}

void main(string str) {
   if (str && (str != "")) {
      if (str == "-r") {
         write("WARNING!!! this is not reversable.\n");
         write("Are you sure you really want to remove your player? (Y|N)\n");
         this_player()->input_to_object(this_object(), "verify_remove");
         return;
      }
      usage();
      return;
   }

   this_player()->do_quit();
}
