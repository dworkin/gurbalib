inherit M_COMMAND;

string *usage(void) {
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
  
   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "cmds");
}

string *get_group_members() {
}

string get_group_name() {
}

int get_group_exp() {
   return 0;
}

int get_group_gold() {
   return 0;
}

/* XXX Lots of work left */

int do_group_hp() {
   string name, *members, *lines;
   int x, maxx, hp, mana, end, maxhp, maxmana, maxend;
   object obj;

   members = get_group_members();
   maxx = sizeof(members);

   lines = ({ "Group: " + get_group_name() + "\n" });
   lines += ({ "----------------------------------" });

   for (x = 0; x < maxx; x++ ) {
      obj = USER_D->find_player(members[x]);
      if (obj) {
         name = uppercase(members[x]);

         if (obj->is_group_leader()) {
            name += "*";
         }

         hp = obj->query_hp();
         maxhp = obj->query_max_hp();
         mana = obj->query_mana();
         maxmana = obj->query_max_mana();
         end = obj->query_end();
         maxend = obj->query_max_end();

         lines += ({ name + "\tHP: " + hp + "/" + maxhp +
            "\tMANA: " + mana + "/" + maxmana + 
            "\tEND: " + end + "/" + maxend + "\n" });
      }
   }
   this_player()->more(lines);
}

int do_group_accept() {
}

int do_group_leave() {
}

int is_leader(object player) {
}

int do_group_status() {
   string *lines, *members;
   int x, maxx;

   members = get_group_members();
   maxx = sizeof(members);

   lines = ({ "Group: " + get_group_name() + "\n" });
   lines += ({ "Group EXP: " + get_group_exp() + "\n" });
   lines += ({ "Group Gold: " + get_group_gold() + "\n" });

   lines += ({ "Members:\n" });
   maxx = sizeof(members);

   for (x = 0; x < maxx; x++) {
      lines += ({ "\t" + members[x] + "\n" });
   }

   this_player()->more(lines);
}

int do_group_split() {
   if (is_leader(this_player())) {
   } else {
      write("You are not the group leader, you cannot split up the booty.\n");
   }
}

int do_group_invite(string who) {
}

int do_group_leader(string who) {
   if (is_leader(this_player())) {
   } else {
      write("You are not the group leader, you cannot change the leader.\n");
   }
}

int do_group_name(string who) {
   if (is_leader(this_player())) {
   } else {
      write("You are not the group leader, you cannot change the group " +
         "name.\n");
   }
}

int do_group_remove(string who) {
   if (is_leader(this_player())) {
   } else {
      write("You are not the group leader, you cannot remove people " +
         "from the group.\n");
   }
}

int do_group_say(string what) {
}

static void main(string arg) {
   string file;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(arg) || (arg == "help")) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
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
/* Need to handle multi args here... */
         break;
   }

   return;
}
