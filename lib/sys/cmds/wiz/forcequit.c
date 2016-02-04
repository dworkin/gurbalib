inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: forcequit [-h] PLAYER" });
   lines += ({ " " });
   lines += ({ "Locates the given PLAYER and forces them to quit the game." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tforcequit sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "quit");

   add_also("wiz", "ban");
   add_also("wiz", "halt");
   add_also("wiz", "heal");
   add_also("wiz", "muzzle");
   add_also("wiz", "zap");
}

static void main(string str) {
   object ob;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   ob = USER_D->find_player(str);
   if (ob) {
      if (ob->is_player() == 1) {
         this_player()->simple_action("$N $vforce " + ob->query_name() +
            " off the game.\n");
         ob->do_quit();
      }
   } else {
      write("You can't seem to find " + str + ".\n");
   }
}
