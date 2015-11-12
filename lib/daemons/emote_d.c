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

   if (!emotes[name]) {
      emotes[name] = ([]);
   }
   emotes[name][rule] = fmt;
   save_me();
}

int is_emote(string name) {
   if (!emotes[name]) {
      return 0;
   } else {
      return 1;
   }
}

string *query_emotes(void) {
   string *values;
 
   values = map_indices(emotes);
   if (!values) {
      return ({ "" });
   }

   return values;
}

string get_random_emote(void) {
   string *values;
   int x;

   values = query_emotes();
   x = sizeof(values);
   x = random(x);

   return values[x];
}

string query_emote(string name, string rule) {
   if (member_map(name, emotes) && member_map(rule, emotes[name])) {
      return emotes[name][rule];
   } 

   return nil;
}

string *query_rules(string name) {
   if (member_map(name, emotes)) {
      return map_indices(emotes[name]);
   }

   return nil;
}

void remove_emote(string name) {
   emotes[name] = nil;
   save_me();
}

string *get_all_emotes(string str, int width) {
   string line, *rules, *lines;
   int i, tmp, max;

   rules = query_emotes();

   lines = ({ "Emotes:" });

   line = "   ";
   max = sizeof(rules) -1;
   if (max >= 0) {
      for (i = 0; i < max; i++) {
         tmp = strlen(rules[i]) + 3 + strlen(line);
         if (tmp >= width) {
            lines += ({ line });
            line = "   " + rules[i] + ", ";
         } else {
            line += rules[i] + ", ";
         }
      }
      line += rules[max];
   }

   lines += ({ line });
   lines += ({ "Total emotes: " + sizeof(rules) });

   return lines;
}

string *show_emote(string str, int width) {
   string *rules, *lines;

   lines = ({ });

   if (!str || str == "") {
      return get_all_emotes(str, width);
   }

   if (is_emote(str)) {
      rules = query_rules(str);

      while (sizeof(rules) > 0) {
         lines += 
            ({ rules[0] + " : \"" + query_emote(str, rules[0]) + "\"" });
         rules -= ({ rules[0] });
      }
   } else {
      lines += ({ "No such emote. \n" });
   }

   return lines;
}
