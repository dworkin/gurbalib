inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: group [-h] [PCOMMAND PLAYER] [GCOMMAND]" });
   lines += ({ "" });
   lines += ({ "Allows you to create groups and work as a team." });
   lines += ({ "" });
   lines += ({ "Valid GCOMMANDS: " });
   lines += ({ "\taccept       Accept an invitation to join a group." });
   lines += ({ "\thp           List each members hp/mana/fatigue" });
   lines += ({ "\tleave        Leave your group." });
   lines += ({ "\tstatus       Display information about the group." });
   lines += ({ "\tsay msg      Send MSG to every group member." });
   lines += ({ "\tsplit        Split your booty, note party must all be " +
      "present." });
   lines += ({ "" });
   lines += ({ "Valid PCOMMANDS: " });
   lines += ({ "\tinvite (PLAYER)       Invite someone to join your group." });
   lines += ({ "\tleader (PLAYER)       Pass leadership of the group to " +
      "another player." });
   lines += ({ "\tname NAME             Set the name of your group." });
   lines += ({ "\tremove (PLAYER)       Remove someone from the group." });

   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tgroup name Raiders" });
   lines += ({ "\tgroup invite sirdude" });
   lines += ({ "\tgroup hp" });
   lines += ({ "\tgroup say Lets attack the frog." });
   lines += ({ "\tgroup split" });
  
   lines += ({ "See also:" });

      lines += ({ "\tcmds" });

   this_player()->more(lines);
}

/* XXX Lots of work left */

int do_group_hp() {
}

int do_group_accept() {
}

int do_group_leave() {
}

int do_group_status() {
}

int do_group_split() {
}

int do_group_invite(string who) {
}

int do_group_leader(string who) {
}

int do_group_name(string who) {
}

int do_group_remove(string who) {
}

int do_group_say(string what) {
}

static void main(string arg) {
   string file;
   if (empty_str(arg) || (arg == "help")) {
      usage();
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      usage();
      return;
   }

   switch (arg) {
      case "hp":
         do_group_hp();
         break;
      case "leave":
         do_group_leave();
         break;
      case "accept":
         do_group_accept();
         break;
      case "status":
         do_group_status();
         break;
      case "split":
         do_group_split();
         break;
      default:
// Need to handle multi args here...
         break;

   return;
}
