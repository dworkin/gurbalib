/* Handle both system wide aliases and wizard aliases. */
mapping player_alias;
mapping wizard_alias;

void restore_me(void);
void save_me(void);

void create(void) {
   player_alias = ([]);
   wizard_alias = ([]);
   restore_me();
}

nomask void restore_me(void) {
   unguarded("restore_object", "/daemons/data/alias_d.o");
}

nomask void save_me(void) {
   unguarded("save_object", "/daemons/data/alias_d.o");
}

void add_player_alias(string cmd, string alias) {
   if (!player_alias)
      player_alias = ([]);

   player_alias[cmd] = alias;
   write("Player alias " + cmd + " added.");
   save_me();
}

void remove_player_alias(string cmd) {
   if (!player_alias)
      player_alias = ([]);

   player_alias[cmd] = nil;
   write("Player alias " + cmd + " removed.");
   save_me();
}

void add_wizard_alias(string cmd, string alias) {
   if (!wizard_alias)
      wizard_alias = ([]);

   wizard_alias[cmd] = alias;
   write("Wizard alias " + cmd + " added.");
   save_me();
}

void remove_wizard_alias(string cmd) {
   if (!wizard_alias)
      wizard_alias = ([]);

   wizard_alias[cmd] = nil;
   write("Wizard alias " + cmd + " removed.");
   save_me();
}

int is_alias(string cmd) {

   if (!player_alias)
      player_alias = ([]);

   if (!wizard_alias)
      wizard_alias = ([]);

   if (player_alias[cmd])
      return 1;

   if (query_wizard(this_player()->query_name())) {
      if (wizard_alias[cmd])
	 return 1;
   }

   return 0;
}

string query_alias(string cmd) {
   if (!player_alias)
      player_alias = ([]);

   if (!wizard_alias)
      wizard_alias = ([]);

   if (player_alias[cmd])
      return player_alias[cmd];

   if (query_wizard(this_player()->query_name())) {
      if (wizard_alias[cmd])
	 return wizard_alias[cmd];
   }
   return nil;
}

string do_expand(string alias, string arg) {
   string *args;
   int i;

   alias = replace_string(alias, "$*", arg);

   if (arg && arg != "") {
      args = explode(arg, " ");

      for (i = 0; i < sizeof(args); i++) {
	 alias = replace_string(alias, "$" + i, args[i]);
      }
   }
   return alias;
}

string expand_alias(string cmd) {
   string alias;
   string arg;

   if (!cmd || cmd == "")
      return "";

   arg = "";

   sscanf(cmd, "%s %s", cmd, arg);

   if (is_alias(cmd)) {
      alias = query_alias(cmd);
      if (!alias)
	 return nil;
      return do_expand(alias, arg);
   } else {
      if (!arg || arg == "")
	 return cmd;
      return cmd + " " + arg;
   }
}

string *show_alias(string type, string str) {
   string *rules, *aliases;
   int i;
   string line;

   rules = ( { } );
   if (!str || str == "") {
      if (!type || type == "" || type == "player") {
	 rules += ( { "Player aliases:\n" } );
	 aliases = map_indices(player_alias);
	 for (i = 0; i < sizeof(aliases); i++) {
	    line += aliases[i] + ", ";
	 }
	 rules += ( { line } );
      }
      if (!type || type == "" || type == "wizard") {
	 rules += ( { "Wizard aliases:\n" } );
	 aliases = map_indices(wizard_alias);
	 for (i = 0; i < sizeof(aliases); i++) {
	    line += aliases[i] + ", ";
	 }
	 rules += ( { line } );
	 return rules;
      }
   }

   if (type == "" || type == "player") {
      if (player_alias[str]) {
	 rules += ( { "Player alias: " + str + " : " + player_alias[str] + 
            "\n" } );
      }
   }

   if (type == "" || type == "wizard") {
      if (wizard_alias[str]) {
	 rules += ( { "Wizard alias: " + str + " : " + wizard_alias[str] + 
            "\n" } );
      }
   }
}
