inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: possess [-h] [MONSTER]" });
   lines += ({ " " });
   lines += ({ "Allows you to possess a monster and control it." });
   lines += ({ "If you type possess with no arguments you will stop " +
      "possessing an object." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpossess rat" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "last");
   add_also("wiz", "locate");
   add_also("wiz", "look");
   add_also("wiz", "mudlist");
   add_also("wiz", "rwho");
   add_also("wiz", "snoop");
   add_also("wiz", "where");
   add_also("wiz", "who");
}

static void main(string str) {
   object ob;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      if (this_user()->query_player()->is_possessing()) {
         write("Your release your grasp on " + this_player()->query_name() +
            ".");
         this_user()->query_player()->query_possessing()->set_possessor(nil);
         this_user()->query_player()->set_possessing(nil);

         return;
      } else {
         write("Please specify what to possess.\n");

         return;
      }
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (this_user()->query_player()->is_possessing()) {
      write("You can't possess more than one being at a time.");
      return;
   }

   ob = this_environment()->present(lowercase(str));
   if (!ob) {
      write("You can't seem to find the " + lowercase(str) + ".");
      return;
   }

   if (ob->is_living()) {
      if (ob->is_player()) {
         write("You can't possess other players.");

         return;
      }

      if (ob->is_possessed()) {
         write("You can't possess a creature someone is already possessing.");

         return;
      }

      this_user()->query_player()->set_possessing(ob);
      ob->set_possessor(this_user()->query_player());
      write("You take control over the " + lowercase(str) + ".\n");
      write("To stop type: possess\n");
   } else {
      write("You can't possess that.");
   }
}
