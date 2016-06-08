#include <type.h>

/*
  You can do the following define to enable debug output
  from the parser daemon.
  Do NOT enable this here!!!
  Add it to /std/include/local_config.h instead, else you 
  will spam every user with this.

  #define DEBUG_PARSE
*/

mapping verbs;
mapping object_rules;
string *names;
string verb_rules; /* the grammar used by parse_string is concatenated from  */
string grammar;    /* these strings, and an optional string in between for   */
                   /* object defined verb rules accessible by this_player(). */

void rescan_verbs(void);
string scan_local_verbs();

void create(void) {
   int i;

   verbs = ([]);
   object_rules = ([]);
   rescan_verbs();
}

string *query_verbs(void) {
   return names;
}

int is_verb(string verb) {
   if (member_array(verb, map_indices(verbs)) != -1) {
      return 1;
   }
   return 0;
}

int call_help(string verb) {
   mixed obj, x;

   obj = verbs[verb];
   x = call_other(obj, "usage");

   if (!x) {
      return 0;
   }
   return 1;
}

/* calls can_x with right number of args for grammar */
int query_can(mixed obj, string func, varargs mixed args ...) {
   mixed x;

   if (sizeof(args) && typeof(args[0]) == T_ARRAY) {
      args = args[0];
   }

   switch (sizeof(args)) {
      case 0:
         x = call_other(obj, func);
         break;
      case 1:
         x = call_other(obj, func, args[0]);
         break;
      case 2:
         x = call_other(obj, func, args[0], args[1]);
         break;
      case 3:
         x = call_other(obj, func, args[0], args[1], args[2]);
         break;
      case 4:
         x = call_other(obj, func, args[0], args[1], args[2], args[3]);
         break;
   }
   if (!x) {
      return 0;
   }

   return 1;
}

/* returns verb object for grammar given.  Scans objects in order of priority.
   Items in player inventory take precedence over items in their environment. */
object query_verb_object(string rule, varargs mixed results) {
   int i, x;
   object *inventory_environment;   /* inventory of environment 
                                           we are scanning */

   rule = "can_" + rule;
   if (!results) {
      results = ( { } );
   }

   /* scan player inventory */
   inventory_environment = this_player()->query_inventory();

   for (i = 0; i < sizeof(inventory_environment); i++) {
      if (function_object(rule, inventory_environment[i])) {
         x = query_can(inventory_environment[i], rule, results);
      }
      if (x) {
         return inventory_environment[i];
      }
   }

   /* scan player environment */
   inventory_environment = ( { this_player()->query_environment() } ) + 
      this_player()->query_environment()->query_inventory();
   for (i = 0; i < sizeof(inventory_environment); i++) {
      if (function_object(rule, inventory_environment[i])) {
         x = query_can(inventory_environment[i], rule, results);
         if (x) {
            return inventory_environment[i];
         }
      }
   }
   return nil;    /* no matches */
}

void add_object_rules(string * rules) {
   object prev_ob;

   prev_ob = previous_object();
   if (typeof(object_rules[prev_ob]) != T_MAPPING) {
      object_rules[prev_ob] = ([]);
   }
   if (typeof(object_rules[prev_ob][rules[0]]) != T_MAPPING) {
      object_rules[prev_ob] = ([rules[0]:rules[1..(sizeof(rules) - 1)]]);
   } else {
      object_rules[prev_ob][rules[0]] += rules[1..(sizeof(rules) - 1)];
   }
}

mapping query_all_object_rules(void) {
   return object_rules;
}

mapping query_objects_rules(object obj) {
   if (typeof(object_rules[obj]) == T_MAPPING) {
      return object_rules[obj];
   }
}

int parse(string str) {
   mixed *result;
   string func, err;
   string local_production_rules;
   object local_verb_object;
   mixed obj;
   int i, returned;

   set_otlvar("last_obj", nil);
   local_production_rules = scan_local_verbs();
   err = catch(result =
      parse_string((verb_rules + local_production_rules + grammar), str));

#ifdef DEBUG_PARSE
   write("result: " + dump_value(result));
#endif
   if (err) {
      int pos;

#ifdef DEBUG_PARSE
      write("error: " + err);
#endif

      if (sscanf(err, "Bad token at offset %d", pos) == 1) {
         write("Invalid character " + str[pos..pos]);
      }
      return 0;
   }

   if (!result) {
      return 0;
   }

#ifdef DEBUG_PARSE
   write("parse_string result: " + dump_value(result));
#endif
   func = "";
   if (sizeof(result) > 1) {
      for (i = 0; i < sizeof(result); i++) {
         switch (typeof(result[i])) {
            case T_OBJECT:
               if (result[i]->is_living()) {
                  func += "liv ";
               } else {
                  func += "obj ";
               }
               break;
            case T_STRING:
               if (i == 0) {
                  func += lowercase(result[i]) + " ";
               } else {
                  func += "str ";
               }
               break;
         }
      }
      func = implode(explode(func, " "), "_");
   } else {
      func = result[0];
   }

#ifdef DEBUG_PARSE
   write("Scanning for local verbs matching grammar...");
#endif

   if (sizeof(result) > 1) {
      local_verb_object =
         query_verb_object(func, result[1..(sizeof(result) - 1)]);
   } else {
      local_verb_object = query_verb_object(func);
   }

   if (local_verb_object) {
      obj = local_verb_object;

#ifdef DEBUG_PARSE
      write("Function : 'can_" + func + "' in object " + dump_value(obj));
#endif
      returned = 1;
   } else {
      obj = verbs[result[0]];

#ifdef DEBUG_PARSE
      write("Function : 'can_" + func + "' in object " + obj);
#endif

      if (sizeof(result) > 1) {
         returned =
            query_can(obj, "can_" + func, result[1..(sizeof(result) - 1)]);
      } else {
         returned = query_can(obj, "can_" + func);
      }
   }

   if (returned == 1) {
#ifdef DEBUG_PARSE
      write("calling : " + "do_" + func);
#endif
      switch (sizeof(result)) {
         case 1:
            call_other(obj, "do_" + func);
            break;
         case 2:
            call_other(obj, "do_" + func, result[1]);
            break;
         case 3:
            call_other(obj, "do_" + func, result[1], result[2]);
            break;
         case 4:
            call_other(obj, "do_" + func, result[1], result[2], result[3]);
            break;
         case 5:
            call_other(obj, "do_" + func, result[1], result[2],
               result[3], result[4]);
            break;
      }
   }

   if (!returned) {
      returned = 0;
   }

   return returned;
}

/* parses an objects verb rules into production rules. */
string parse_verb_rules(mapping rules) {
   int i, j, k, ofix;
   string output;
   string *info, *words;

   output = "";
   info = map_indices(rules);

   /* each verb */
   for (i = 0; i < sizeof(info); i++) {

      /* each rule for a verb */
      for (j = 0; j < sizeof(rules[info[i]]); j++) {

         output += "Sentence: '" + info[i] + "' ";
         words = explode(rules[info[i]][j], " ");
         /* each word for a rule */
         for (k = 0; k < sizeof(words); k++) {
            switch (words[k]) {
               case "OBJ":
               case "OBJA":
               case "OBJI":
               case "OBJE":
               case "OBJC":
               case "LIV":
                  output += words[k] + " ";
                  break;
               case "OBJX":
                  output += "OBJX ";
                  ofix = 1;
                  break;
               default:
                  output += "'" + words[k] + "' ";
            }
         }

         if (ofix) {
            output += "? fix_order ";
         }
         ofix = 0;
      }
   }

   return output;
}

void rescan_verbs(void) {
   mixed *list;
   string verb, *words;
   int i, j, k, ofix;
   mixed info;

   list = get_dir("/cmds/verb/*.c");
   names = list[0];

   for (i = 0; i < sizeof(names); i++) {
      names[i] = names[i][..(strlen(names[i]) - 3)];
      verb = "/cmds/verb/" + names[i];
      verbs[names[i]] = verb;
   }

   verb_rules = "whitespace = / / word = /[a-zA-Z]+/ number = /[0-9]+/ ";

   for (i = 0; i < sizeof(names); i++) {
      write("Scanning " + names[i] + "(" + verbs[names[i]] + ")");

      info = call_other(verbs[names[i]], "query_verb_info");

      write("Verb info: " + dump_value(info));

      if (sizeof(info) > 0) {
         /* Rules and aliases */

         for (j = 0; j < sizeof(info); j++) {
            verb_rules += "Sentence: '" + names[i] + "' ";

            words = explode(info[j], " ");
            for (k = 0; k < sizeof(words); k++) {

               switch (words[k]) {
                  case "OBJ":
                  case "OBJA":
                  case "OBJI":
                  case "OBJE":
                  case "OBJC":
                  case "LIV":
                     verb_rules += words[k] + " ";
                     break;
                  case "OBJX":
                     verb_rules += "OBJX ";
                     ofix = 1;
                     break;
                  default:
                     verb_rules += "'" + words[k] + "' ";
               }
            }
            if (ofix) {
               verb_rules += "? fix_order ";
            }
            ofix = 0;
         }
      }
   }

   grammar = "OBJ: Object ? find_direct_object\n" +
      "OBJA: Object ? construct_obj_packet\n" +
      "OBJI: Object ? find_inv_object\n" +
      "OBJE: Object ? find_environment_object\n" +
      "LIV: Object ? find_living_object\n" +
      "OBJC: Object ? find_container_object\n" +
      "OBJX: Object\n" +
      "Object: Article_List Adjective_List Noun Obj_Index\n" +
      "Article: 'the'\n" +
      "Article: 'a'\n" +
      "Article: 'an'\n" +
      "Article: 'any'\n" +
      "Article: 'my'\n" +
      "Article: 'in'\n" +
      "Article: 'at'\n" +
      "Article: 'on'\n" +
      "Article: 'from'\n" +
      "Article:\n" +
      "Article_List: Article ? group_results\n" +
      "Adjectives: word Adjectives\n" +
      "Adjectives:\n" +
      "Adjective_List: Adjectives ? group_results\n" +
      "Preposition: word\n" +
      "Preposition:\n" +
      "Preposition_List: Preposition ? group_results\n" +
      "Noun: word\n" +
      "words: word ? group_results\n" +
      "Index: number\n" +
      "Index:\n" +
      "Obj_Index: Index ? define_obj_index";
}

string scan_local_verbs(void) {
   int i;
   string production_rules;
   object *inventory_environment;
   object room;

   production_rules = "";

   /* scan player inventory */
   inventory_environment = this_player()->query_inventory();

   for (i = 0; i < sizeof(inventory_environment); i++) {
      if (typeof(object_rules[inventory_environment[i]]) != T_MAPPING) {
         continue;
      }
      production_rules +=
         parse_verb_rules(object_rules[inventory_environment[i]]);
   }

   /* scan environment and contents of environment */
   room = this_player()->query_environment();
   if (room) {
      inventory_environment = ( { room } ) +
         room->query_inventory();
      for (i = 0; i < sizeof(inventory_environment); i++) {
         if (typeof(object_rules[inventory_environment[i]]) != T_MAPPING) {
            continue;
         }
         production_rules +=
            parse_verb_rules(object_rules[inventory_environment[i]]);
      }
   }
   return production_rules;
}

static mixed *construct_obj_packet(mixed * mpTree) {
   string res;
   int i;

#ifdef DEBUG_PARSE
   write("construct_obj_packet("
      + dump_value(mpTree[0]) + ","
      + dump_value(mpTree[1]) + ","
      + dump_value(mpTree[2]) + "," + dump_value(mpTree[3]) + ")\n");
#endif

   res = "";

   for (i = 0; i < sizeof(mpTree[1]); i++) {
      res += mpTree[1][i] + " ";
   }

   res += mpTree[2];

   return ( { res } );
}

static mixed *find_container_object(mixed * mpTree) {
   object ob;

#ifdef DEBUG_PARSE
   write("find_container_object("
      + dump_value(mpTree[0]) + ","
      + dump_value(mpTree[1]) + ","
      + dump_value(mpTree[2]) + "," + dump_value(mpTree[3]) + ")\n");
#endif

   if (!get_otlvar("last_obj")) {
      return nil;
   }

   if (sizeof(mpTree[1]) > 0) {
      ob = get_otlvar("last_obj")->find_adjs_object_num(mpTree[1],
         mpTree[2], mpTree[3]);
   } else {
      ob = get_otlvar("last_obj")->find_object_num(mpTree[2], mpTree[3]);
   }

   if (!ob) {
      return nil;
   }

   set_otlvar("last_obj", ob);
   return (( { ob } ));
}

static mixed *find_living_object(mixed * mpTree) {
   object ob;

#ifdef DEBUG_PARSE
   write("find_living_object("
      + dump_value(mpTree[0]) + ","
      + dump_value(mpTree[1]) + ","
      + dump_value(mpTree[2]) + "," + dump_value(mpTree[3]) + ")\n");
#endif

   if (sizeof(mpTree[1]) > 0) {
      ob = this_environment()->find_adjs_object_num(mpTree[1],
         mpTree[2], mpTree[3]);
   } else {
      ob = this_environment()->find_object_num(mpTree[2], mpTree[3]);
   }

   if (ob) {
      if (ob->is_living()) {
         set_otlvar("last_obj", ob);
         return (({ ob }));
      }
   }

   return nil;
}

static mixed *find_direct_object(mixed * mpTree) {
   object ob;

#ifdef DEBUG_PARSE
   write("find_direct_object("
      + dump_value(mpTree[0]) + ","
      + dump_value(mpTree[1]) + ","
      + dump_value(mpTree[2]) + "," + dump_value(mpTree[3]) + ")\n");
#endif

   if (sizeof(mpTree[1]) > 0) {
      /* With adjective */
      ob = this_environment()->find_adjs_object_num(mpTree[1],
         mpTree[2], mpTree[3]);
      if (!ob) {
         ob = this_player()->find_adjs_object_num(mpTree[1], mpTree[2],
            mpTree[3]);
         if (!ob) {
            return nil;
         }
      }
   } else {
      ob = this_environment()->find_object_num(mpTree[2], mpTree[3]);
      if (!ob) {
         ob = this_player()->find_object_num(mpTree[2], mpTree[3]);
         if (!ob) {
            return nil;
         }
      }
   }

   if (ob->is_living()) {
      return nil;
   }

   set_otlvar("last_obj", ob);
   return (( { ob } ));
}

static mixed *find_inv_object(mixed * mpTree) {
   object ob;

#ifdef DEBUG_PARSE
   write("find_inv_object("
      + dump_value(mpTree[0]) + ","
      + dump_value(mpTree[1]) + ","
      + dump_value(mpTree[2]) + "," + dump_value(mpTree[3]) + ")\n");
#endif

   if (sizeof(mpTree[1]) > 0) {
      /* With adjective */
      ob = this_player()->find_adjs_object_num(mpTree[1], mpTree[2], mpTree[3]);
   } else {
      /* Without adjective */
      ob = this_player()->find_object_num(mpTree[2], mpTree[3]);
   }
   if (!ob) {
      return nil;
   }

   set_otlvar("last_obj", ob);
   return (( { ob } ));
}

static mixed *find_environment_object(mixed * mpTree) {
   object ob;

#ifdef DEBUG_PARSE
   write("find_environment_object("
      + dump_value(mpTree[0]) + ","
      + dump_value(mpTree[1]) + ","
      + dump_value(mpTree[2]) + "," + dump_value(mpTree[3]) + ")\n");
#endif

   if (sizeof(mpTree[1]) > 0) {
      ob = this_environment()->find_adjs_object_num(mpTree[1], mpTree[2],
         mpTree[3]);
   } else {
      ob = this_environment()->find_object_num(mpTree[2], mpTree[3]);
   }
   if (!ob) {
      return nil;
   }

   set_otlvar("last_obj", ob);
   return (( { ob } ));
}

static mixed *define_obj_index(mixed * mpTree) {
   if (!mpTree || !sizeof(mpTree)) {
      return (( { 1 } ));
   }
   return (( { (int)mpTree[0] } ));
}

static mixed *group_results(mixed * mpTree) {
   return (( { mpTree } ));
}

static mixed *fix_order(mixed * mpTree) {
   mixed obj;
   int i;

#ifdef DEBUG_PARSE
   write(dump_value(mpTree) + "\n");
   write("fix_order("
      + dump_value(mpTree[0]) + ","
      + dump_value(mpTree[1]) + ","
      + dump_value(mpTree[2]) + ","
      + dump_value(mpTree[3]) + ","
      + dump_value(mpTree[4]) + ","
      + dump_value(mpTree[5]) + "," + dump_value(mpTree[6]) + ")\n");
#endif
   set_otlvar("last_obj", mpTree[6]);
   obj = find_container_object(mpTree[1..4]);

   if (typeof(obj) == T_ARRAY) {
      mpTree = ( { mpTree[0] } ) + obj + ( { mpTree[5], mpTree[6] } );
   } else {
      mpTree = ( { mpTree[0], mpTree[3] } ) + mpTree[5..6];
   }

   return mpTree;
}

void upgraded(void) {
   if (!object_rules) {
      object_rules = ([]);
      rescan_verbs();
   }
}
