inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: emoteadm -h" });
   lines += ({ "Usage: emoteadm show [EMOTE]    show the entries for EMOTE" });
   lines += ({ "\tIf EMOTE is missing show all emotes registered." });
   lines += ({ "Usage: emoteadm del EMOTE     delete the entries for EMOTE" });
   lines += ({ "Usage: emoteadm add NAME [RULE] FORMAT" });
   lines += ({ " " });
   lines += ({ "Add an emote to the emote database." });
   lines += ({ "NAME is the thing players will type for the emote." });
   lines += ({ "RULE if provided is one of the following: LIV|STR|OBJ" });
   lines += ({ "It only applies if the target of your emote is of that type."
   });
   lines += ({ "For emotes without a target, you do not provide a rule." });
   lines += ({ "Format defines what the emote will do." });
   lines += ({ "For example, if you do \"add blink $N blink.\"" });
   lines += ({ "\tYou will see You blink." });
   lines += ({
      "\tEveryone else will see Sirdude blink. (If your name is sirdude)"
   });

   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t$N\tUpper case name of the player emoting" });
   lines += ({ "\t$n\tLower case name of the player emoting" });
   lines += ({
      "\t$vVERB\tDefines VERB as a verb and the parser will change output."
   });
   lines += ({ "\t$T\tUpper case name of target." });
   lines += ({ "\t$t\tLower case name of target." });
   lines += ({ "\t$O\tUpper case name of object." });
   lines += ({ "\t$o\tLower case name of object." });
   lines += ({ "\t$p\tPossesive" });

   lines += ({ "Examples:" });
   lines += ({ "\temoteadm add blink $N $sblink." });
   lines += ({ "\temoteadm add LIV $N $vblink at $t" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "alias");
   add_also("player", "cmds");
   add_also("player", "emote");
   add_also("player", "help");

   add_also("wiz", "aliasadm");
   add_also("wiz", "domain");

   add_also("admin", "cmdadm");
   add_also("admin", "coloradm");
   add_also("admin", "emotediff");
   add_also("admin", "rehash");
}

void delete_emote(string str) {
   if (EMOTE_D->is_emote(str)) {
      EMOTE_D->remove_emote(str);
      write("Emote " + str + " removed.\n");
   } else {
      write("No such emote.\n");
   }
}

void add_emote(string str) {
   string name, tmp;
   string rule, fmt;

   if (sscanf(str, "%s %s", name, tmp) != 2) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(tmp, "%s %s", rule, fmt) != 2) {
      fmt = rule;
      rule = "STR";
   } else if ((uppercase(rule) != "LIV") &&
      (uppercase(rule) != "STR") && (uppercase(rule) != "OBJ")) {
      fmt = rule + " " + fmt;
      rule = "";
   }

   EMOTE_D->add_emote(name, rule, fmt);
   write("Emote " + name + " added.\n");
}

static void main(string str) {
   string name, fmt, *lines;
   int width;

   if (!alsos) {
      setup_alsos();
   }

   width = this_player()->query_width();

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (str == "show") {
      lines = EMOTE_D->show_emote("", width);
      this_player()->more(lines);
      return;
   }

   if (sscanf(str, "%s %s", name, fmt) != 2) {
      this_player()->more(usage());
      return;
   }

   if (name == "show") {
      lines = EMOTE_D->show_emote(fmt, width);

      this_player()->more(lines);
      return;
   } else if ((name == "del") || (name == "delete") || (name == "rm") ||
      (name == "remove")) {
      delete_emote(fmt);
      return;
   } else if (name != "add") {
      this_player()->more(usage());
      return;
   }
   add_emote(fmt);
}
