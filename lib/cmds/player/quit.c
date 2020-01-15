inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: quit [-h] [-r]" });
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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "cast");
   add_also("player", "eat");
   add_also("player", "enter");
   add_also("player", "follow");
   add_also("player", "go");
   add_also("player", "pray");
   add_also("player", "query");
   add_also("player", "wimpy");

   add_also("wiz", "aload");
   add_also("wiz", "forcequit");
}

void verify_remove(string str) {
   if (str == "Y" || str == "y") {
      USER_D->delete_user(this_player()->query_name());
   } else {
      write("Removal cancelled.\n");
   }
}

static void main(string str) {

   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      if (str == "-r") {
         write("WARNING!!! this is not reversible.\n");
         write("Are you sure you really want to remove your player? (Y|N)\n");
         this_player()->input_to_object(this_object(), "verify_remove");
         return;
      }
      this_player()->more(usage());
      return;
   }

   if (this_player()->is_resting()) {
      this_player()->rest();
   }

   this_player()->do_quit();
}
