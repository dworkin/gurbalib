inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: promote [-h] PLAYER [player|wiz|admin]" });
   lines += ({ "" });
   lines += ({ "Promote is kind of a misnomer, this command is used to change,"
      });
   lines += ({ "the level of a given player, to the level you specify." });
   lines += ({ "We hope that you will be promoting rather than demoting " +
      "players." });
   lines += ({ "If a wiz directory does not exist it will be created." });
   lines += ({ "Promoting a wizard or admin to a player will not remove " +
      "their wiz dir." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tpromote sirdude admin\tMake sirdude an admin" });
   lines += ({ "\tpromote sirdude wiz\tMake sirdude a wizard" });
   lines += ({ "\tpromote sirdude player\tMake sirdude a normal player" });
   lines += get_alsos();

   lines += ({ "\tban, forcequit, muzzle, rmuser, zap" });

   return lines;
}

void setup_alsos() {
   add_also("wiz", "ban");
   add_also("wiz", "forcequit");
   add_also("wiz", "muzzle");
   add_also("wiz", "zap");

   add_also("admin", "rmuser");
}

void display_level(string str) {

   if (query_admin(str)) {
      write("User: " + str + " is currently a admin\n");
      return;
   }
   if (query_wizard(str)) {
      write("User: " + str + " is currently a wiz\n");
      return;
   }
   if (USER_D->user_exists(str)) {
      write("User: " + str + " is currently a player\n");
      return;
   }

   write("Who are you trying to promote?\n");
}

static void main(string str) {
   string who, what;
   int numargs;

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
   if (sscanf(str, "%s %s", who, what) != 2) {
      display_level(str);
      return;
   }
   if (!USER_D->user_exists(who)) {
      write("No such user: " + who + ".\n");
      return;
   }

   if (this_player()->query_name() == who) {
      write("You can not promote yourself.\n");
      return;
   }

   what = lowercase(what);
   if (what == "admin") {
      USER_D->make_admin(who);
   } else if ((what == "wiz") || (what == "wizard")) {
      USER_D->make_wizard(who);
   } else if ((what == "player") || (what == "mortal")) {
      USER_D->make_mortal(who);
   } else {
      this_player()->more(usage());
   }
}
