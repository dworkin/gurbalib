#include <type.h>
inherit "/std/body/size";	/* satch */
inherit "/std/modules/m_autoload_filename";

static string brief_desc;
string long_desc;
static object object_environment;
static string *ids;
static string *adjs;
static int object_size;
string proper_name;
static mapping object_commands;
static string detailed_desc;
private int configured;
static int eatable;
static int gettable;
static int object_value;

void setup();

void create(void) {
   string tmp;

   if (configured++)
      return;

   brief_desc = "";
   ids = ( { "nondescript thing" } );
   adjs = ( { } );

   tmp = file_name();
   set_autoload_filename(tmp);

   if (!clone_num()) {
      OBJECT_D->register_object(this_object());
   } else {
      OBJECT_D->register_clone(this_object());
   }
}

int is_living(void) {
   return 0;
}

int is_player(void) {
   return 0;
}

void set_id(string str, varargs mixed args ...) {
   int i;

   if (sizeof(args) && typeof(args[0]) == T_ARRAY) {
      args = args[0];
   }

   ids = ( { str } );
   for (i = 0; i < sizeof(args); i++) {
      ids += ( { (string) args[i] } );
   }
}

void add_id(string str, varargs mixed args ...) {
   int size;

   ids -= ( { "nondescript thing" } );
   if (sizeof(args) && typeof(args[0]) == T_ARRAY) {
      args = args[0];
   }
   size = sizeof(ids);
   /* fix args to set_id so that ids[0] preserved after adding new ids */
   switch (size) {
      case 0:
	 set_id(str, args);
	 break;
      case 1:
	 set_id(ids[0], ( { str } ) + args);
	 break;
      default:
	 set_id(ids[0], ( { str } ) + args + ids[1..(size - 1)]);
   }
}

void add_ids(string str, varargs mixed args ...) {
   add_id(str, args);
}

string query_id(void) {
   return ids[0];
}

string *query_ids(void) {
   return ids;
}

int is_id(string id) {
   int i;
   for (i = 0; i < sizeof(ids); i++) {
      if (ids[i] == id)
	 return 1;
   }
   return 0;
}

void set_adj(string str, varargs mixed args ...) {
   int i;

   adjs = ( { str } );
   for (i = 0; i < sizeof(args); i++) {
      adjs += ( { (string) args[i] } );
   }
}

void add_adj(string str, varargs mixed args ...) {
   int i;

   if (!adjs)
      adjs = ( { } );
   adjs += ( { str } );
   for (i = 0; i < sizeof(args); i++) {
      adjs += ( { (string) args[i] } );
   }
}

string *query_adjs(void) {
   return adjs;
}

string query_adj(void) {
   if (sizeof(adjs) == 0)
      return "";
   return adjs[0];
}

int is_adj(string adj) {
   int i;

   for (i = 0; i < sizeof(adjs); i++) {
      if (adjs[i] == adj)
	 return 1;
   }
   return 0;
}

void set_brief(string str) {
   brief_desc = str;
}

void set_in_room_desc(string str) {
   brief_desc = str;
}

string query_in_room_desc(void) {
   return brief_desc;
}

string query_brief(void) {
   if (!brief_desc || brief_desc == "") {
      if (!query_adj() || query_adj() == "") {
	 brief_desc = article(query_id()) + " " + query_id();
      } else {
	 brief_desc = article(query_adj()) + " " + query_adj() + " "
	    + query_id();
      }
   }
   return brief_desc;
}

void set_long(string str) {
   long_desc = str;
}

string query_long(void) {
   return long_desc;
}

void set_proper_name(string name) {
   proper_name = name;
}

string query_proper_name(void) {
   return proper_name;
}

object query_environment(void) {
   return object_environment;
}

void set_environment(object ob) {
   console_msg("set_environment() : " + dump_value(ob, ([])) + "\n");
   object_environment = ob;
}

void destruct(void) {
   if (object_environment)
      object_environment->remove_object(this_object());

   if (clone_num() == 0) {
      OBJECT_D->unregister_object(this_object());
   } else {
      OBJECT_D->unregister_clone(this_object());
   }
   destruct_object(this_object());
}

nomask int move(mixed destination) {
   mixed err;
   object dest;

   if (!destination)
      return 0;

   if (typeof(destination) == T_STRING) {
      /* Remove trailing .c */
      if (destination[strlen(destination) - 2..] == ".c")
	 destination = destination[..strlen(destination) - 3];
      dest = find_object(destination);
      if (!dest)
	 dest = compile_object(destination);
   } else {
      dest = destination;
   }

   if (!dest)
      return 0;
   if (object_environment == dest)
      return 0;

   err = dest->receive_object(this_object());

   if (!err || (err != 1)) {
      if (err)
	 write("Error in move:" + err + "\n");
      else
	 write("Error in move.\n");
      return 0;
   }

   if (object_environment) {
      if (object_environment->is_living()) {
	 if (sizeof(this_object()->query_object_commands()) > 0) {
	    string *objcmds;
	    int i;

	    objcmds = this_object()->query_object_commands();
	    for (i = 0; i < sizeof(objcmds); i++) {
	       object_environment->remove_item_command(objcmds[i]);
	    }
	 }
      }

      object_environment->remove_object(this_object());
   }

   object_environment = dest;

   if (object_environment->is_living()) {
      if (sizeof(this_object()->query_object_commands()) > 0) {
	 string *objcmds;
	 int i;

	 objcmds = this_object()->query_object_commands();
	 for (i = 0; i < sizeof(objcmds); i++) {
	    object_environment->add_item_command(objcmds[i], this_object());
	 }
      }
   }

   return 1;
}

nomask void add_verb_rules(string verb, varargs mixed rules) {
   switch (typeof(rules)) {
      case T_NIL:
	 PARSE_D->add_object_rules(( { verb, ""} ));
	 break;
      case T_STRING:
	 PARSE_D->add_object_rules(( { verb, rules} ));
	 break;
      case T_ARRAY:
	 PARSE_D->add_object_rules(( { verb} ) + rules);
	 break;
   }
   return;
}

nomask mapping query_verb_rules() {
   return PARSE_D->query_objects_rules(this_object());
}

void add_object_command(string command, string function) {
   if (!object_commands) object_commands = ([ ]);
   if (!object_commands[command]) 
      object_commands += ([command:function]);
   else 
      object_commands[command] = function;
}

void remove_object_command(string command) {
   object_commands[command] = nil;
}

string query_object_command(string command) {
   return object_commands[command];
}

string *query_object_commands(void) {
   string *keys;

   if (!object_commands)
      object_commands = ([ ]);
   keys = map_indices(object_commands);

   return keys;
}

void set_eatable(int value) {
   eatable = value;
}

int is_eatable() {
   return eatable;
}

void set_detailed_desc(string desc) {
   detailed_desc = desc;
}

string query_detailed_desc(void) {
   return detailed_desc;
}

void upgraded() {
   if (clone_num() != 0) {
      setup();
   }
}

void set_value(int val) {
   object_value = val;
}

int query_value(void) {
   return object_value;
}

int is_gettable(void) {
   return gettable;
}

void set_gettable(int get) {
   gettable = get;
}

