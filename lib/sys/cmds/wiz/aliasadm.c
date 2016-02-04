inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: aliasadm -h" });
   lines += ({ "Usage: aliasadm show [ALIAS]    show the global entries " +
      "for ALIAS"
   });
   lines += ({ "\tIf ALIAS is missing show all global aliases registered." });
   lines += ({ "Usage: aliasadm del ALIAS     delete the entries for ALIAS" });
   lines += ({ "Usage: aliasadm add TYPE NAME FORMAT" });
   lines += ({ " " });
   lines += ({ "Add an alias to the alias database." });
   lines += ({ "TYPE is \"player\" or \"wiz\"" });
   lines += ({ "NAME is the new command name for the alias." });
   lines += ({ "Format defines what the alias will do." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\taliasadm add player a attack $*" });
   lines += ({ "\taliasadm add wiz z update $*" });
   lines += ({ "\taliasadm show a" });
   lines += ({ "\taliasadm del a" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "alias");
   add_also("player", "cmds");
   add_also("player", "emote");
   add_also("player", "help");

   add_also("wiz", "domain");
   add_also("wiz", "emote");
   add_also("wiz", "emoteadm");

   add_also("admin", "cmdadm");
   add_also("admin", "coloradm");
   add_also("admin", "emotediff");
   add_also("admin", "rehash");
}

void delete_alias(string str) {

   if (ALIAS_D->is_alias(str)) {
      ALIAS_D->remove_player_alias(str);
      ALIAS_D->remove_wizard_alias(str);
   } else {
      write("No such alias.\n");
   }
}

void add_alias(string str) {
   string type, name, fmt, tmp;

   if (sscanf(str, "%s %s", type, tmp) != 2) {
      this_player()->more(usage());
      return;
   }
   if ((type != "wiz") && (type != "wizard") && (type !="player")) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(tmp, "%s %s", name, fmt) != 2) {
      this_player()->more(usage());
      return;
   }
   if (type == "player") {
      ALIAS_D->add_player_alias(name, fmt);
   } else {
      ALIAS_D->add_wizard_alias(name, fmt);
   }
}

static void main(string str) {
   string name, fmt, *lines;

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

   if (str == "show") {
      lines = ALIAS_D->show_alias("", "");
      this_player()->more(lines);
      return;
   }

   if (sscanf(str, "%s %s", name, fmt) != 2) {
      this_player()->more(usage());
      return;
   }

   if (name == "show") {
      lines = ALIAS_D->show_alias("", fmt);
      this_player()->more(lines);
      return;
   } else if ((name == "del") || (name == "delete") || (name == "rm") ||
      (name == "remove")) {
      delete_alias(fmt);
      return;
   } else if (name != "add") {
      this_player()->more(usage());
      return;
   }

   add_alias(fmt);
}
