inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: summon [-h] PLAYER" });
   lines += ({ " " });
   lines += ({ "Find PLAYER, print their current location, and then bring " +
      "them here." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tsummon guest" });
   lines += ({ "See also:" });
   lines += ({ "\tgoto, home, where" });

   this_player()->more(lines);
}

static void main(string str) {
   object usr;

   if (!str || (str == "")) {
      write("Get whom?");
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   usr = USER_D->find_player(lowercase(str));
   if (usr) {
      if (usr->query_environment() != this_player()->query_environment()) {
	 mixed desc;
	 write("We're summoning " + str + ", who is currently here: " +
	    usr->query_environment()->file_name());
	 usr->message("%^RED%^" +
	    this_player()->query_Name() + " requests your presence.%^RESET%^");
	 usr->query_environment()->tell_room(usr, usr->query_Name() +
	    " disappears in a flurry of fluff.\n");
	 usr->move(this_player()->query_environment());
	 usr->message("You abruptly find yourself somewhere else.\n");
	 usr->do_look(0);
	 usr->query_environment()->tell_room(usr, usr->query_Name() +
	    " appears in a cloud of fluff.\n");
      } else {
	 write(capitalize(str) + " is already here.\n");
      }
   } else {
      write("Unable to find " + str + ".\n");
   }
}
