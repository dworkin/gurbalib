mapping emotes;
#define DATAFILE "/daemons/data/emote_d.o"

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);
}

void create(void) {
   if (file_exists(DATAFILE)) {
      restore_me();
   } else {
      emotes = ([
         "bow": ([ "":"$N $vbow.",
                  "LIV":"$N $vbow to $T."
         ])
      ]);
      save_me();
   }
}

void add_emote(string name, string rule, string fmt) {
   if (rule != "STR" && rule != "LIV" && rule != "OBJ") {
      rule = "";
   }

   if (!emotes[name])
      emotes[name] = ([]);
   emotes[name][rule] = fmt;
   save_me();
}

int is_emote(string name) {
   if (!emotes[name])
      return 0;
   else
      return 1;
}

string *query_emotes(void) {
   return map_indices(emotes);
}

string query_emote(string name, string rule) {
   return emotes[name][rule];
}

string *query_rules(string name) {
   return map_indices(emotes[name]);
}

void remove_emote(string name) {
   emotes[name] = nil;
   save_me();
}

string *show_emote(string str, int width) {
   string *rules, *lines;
   int i, tmp;
   string line;

   lines = ({ });

   if (!str || str == "") {
      rules = query_emotes();

      lines = ({ "Emotes:" });

      line = "   ";
      for (i = 0; i < sizeof(rules); i++) {
         tmp = strlen(rules[i]) + 3 + strlen(line);
         if (tmp >= width) {
            lines += ({ line });
            line = "   " + rules[i] + ", ";
         } else {
	    line += rules[i] + ", ";
         }
      }
      lines += ( {line } );
      lines += ( { "Total emotes: " + sizeof(rules) } );

      return lines;
   }
   if (is_emote(str)) {

      rules = query_rules(str);

      while (sizeof(rules) > 0) {
	 lines += 
            ( { rules[0] + " : \"" + query_emote(str, rules[0]) + "\"" } );
	 rules -= ( { rules[0] } );
      }
   } else {
      lines += ( { "No such emote. \n" } );
   }

   return lines;
}
