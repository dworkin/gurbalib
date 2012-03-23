void usage() {
   string *lines;
   lines = ( {
      });

   lines += ( { "Usage: aliasadm -h" } );
   lines += ( { "Usage: aliasadm show [ALIAS]    show the global entrys " +
      "for ALIAS"
   } );
   lines += ( { "\tIf ALIAS is missing show all global aliases registered." } );
   lines += ( { "Usage: aliasadm del ALIAS     delete the entrys for ALIAS" } );
   lines += ( { "Usage: aliasadm add TYPE NAME FORMAT" } );
   lines += ( { "Add an alias to the alias database." } );
   lines += ( { "TYPE is \"player\" or \"wiz\"" } );
   lines += ( { "NAME is the new command name for the alias." } );
   lines += ( { "Format defines what the alias will do." } );
   lines += ( { "Options:" } );
   lines += ( { "\t-h\tHelp, this usage message." } );
   lines += ( { "Examples:" } );
   lines += ( { "\taliasadm add " } );
   lines += ( { "\taliasadm add " } );
   this_player()->more(lines);
}

void delete_alias(string str) {
   if (ALIAS_D->is_alias(str)) {
      ALIAS_D->remove_alias(str);
      write("Alias " + str + " removed.\n");
   } else {
      write("No such alias.\n");
   }
}

void add_alias(string str) {
   string name, tmp, rule, fmt;

   if (sscanf(str, "%s %s", name, tmp) != 2) {
      usage();
      return;
   }

   if (sscanf(tmp, "%s %s", rule, fmt) != 2) {
      fmt = rule;
      rule = "STR";
   } else if (uppercase(rule) != "LIV" &&
      uppercase(rule) != "STR" && uppercase(rule) != "OBJ") {
      fmt = rule + " " + fmt;
      rule = "";
   }

   EMOTE_D->add_alias(name, fmt);
   write("Alias " + name + " added.\n");
}

void main(string str) {
   string name, fmt;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (str == "show") {
      ALIAS_D->show_alias("", "");
      return;
   }

   if (sscanf(str, "%s %s", name, fmt) != 2) {
      usage();
      return;
   }

   if (name == "show") {
      ALIAS_D->show_emote(fmt);
      return;
   } else if (name == "del" || name == "delete" || name == "rm" ||
      name == "remove") {
      delete_alias(fmt);
      return;
   } else if (name != "add") {
      usage();
      return;
   }
   add_alias(fmt);
}
