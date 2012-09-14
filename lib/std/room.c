#include <type.h>

inherit cont CONTAINER;
inherit M_FAKE_OBJECT;

static mapping exits;
static mapping hidden_exits;
static mapping areas;
static mapping room_commands;
static int last_exit;
static int weather;
static int light;

void setup(void);

void create(void) {
   cont::create();
   add_event("body_enter");
   add_event("body_leave");
   add_event("body_look");
   add_event("body_look_at");
   add_event("room_message");
   EVENT_D->subscribe_event("clean_up");
   exits = ([]);
   hidden_exits = ([]);
   areas = ([]);
   room_commands = ([]);
   last_exit = 0;
   light = 1;
   setup();
}

int is_room() {
   return 1;
}

void set_light(int flag) {
   light = flag;
}

int query_dark() {
   object* objs;
   int x;

   if (light)
      return 0;

   if (is_container()) {
      objs = query_inventory();
      for (x=sizeof(objs); x >= 0; x--) {
         /* XXX Need to check for lights in the room... recursively... */
         if (objs->is_lit()) return 1;
      }
   }

   return 1;
}

void set_weather(int flag) {
   weather = flag;
}

int query_weather(void) {
   return weather;
}

void add_area(string str) {
 areas += ([str:1]);
}

int query_in_area(string str) {
   if (areas[str])
      return 1;
   else
      return 0;
}

string *query_areas() {
   return map_indices(areas);
}

void set_exits(mapping ex) {
   exits = ex;
}

void set_hidden_exits(mapping ex) {
   hidden_exits = ex;
}

void add_exit(string direction, string file) {
 exits += ([direction:file]);
}

void remove_exit(string direction) {
   exits[direction] = nil;
}

void add_hidden_exit(string direction, string file) {
 hidden_exits += ([direction:file]);
}

void remove_hidden_exit(string direction) {
   hidden_exits[direction] = nil;
}

mapping query_exits(void) {
   return exits;
}

mapping query_hidden_exits(void) {
   return hidden_exits;
}

string *query_exit_indices(void) {
   return map_indices(exits);
}

string *query_hidden_exit_indices(void) {
   return map_indices(hidden_exits);
}

string query_exit(string direction) {
   return exits[direction];
}

string query_hidden_exit(string direction) {
   return hidden_exits[direction];
}

/* Attempts to find the actual room object attached to a given exit.
  Will compile it if necessary.
  Cerihan - 3/13/09
*/
object query_exit_room(string direction) {
   string exit;
   object qroom;

   exit = query_exit(direction);
   if (!exit)
      return nil;

   qroom = find_object(exit);
   if (!qroom)
      qroom = compile_object(exit);

   return qroom;
}

string query_desc(varargs int brief) {
   string text;
   int count;
   int size;
   object *inventory;
   mapping compacted_inv;

   if (!brief)
      brief = 0;
   text = "%^ROOM_NAME%^" + query_brief() + "%^RESET%^";

   text += " %^ROOM_EXIT%^[ exits: ";

   if (!exits || map_sizeof(exits) == 0) {
      text += "none ";
   } else {
      for (count = 0; count < map_sizeof(exits); count++) {
	 text += map_indices(exits)[count] + " ";
      }
   }

   text += "]%^RESET%^\n";
   text += "%^ROOM_DESC%^" + query_long() + "%^RESET%^";
   text += "\n";

   inventory = query_inventory();

   if (inventory && sizeof(inventory) > 1) {
      string desc;

      compacted_inv = ([]);

      /* There is something in the room */

      text += "\nYou see:\n";

      for (count = 0; count < sizeof(inventory); count++) {
	 if (!inventory[count]->is_living()) {
	    desc =
	       "  %^OBJ_BRIEF%^" + capitalize(inventory[count]->query_brief()) +
	       "%^RESET%^";
	 } else {
	    mixed x;
	    string pc;
	    if (inventory[count] == this_player())
	       continue;
	    x = inventory[count]->query_idle();
	    pc =
	       inventory[count]->is_player()? "%^PLAYER%^" : "%^NPC_FRIENDLY%^";
	    if (x && x > 60) {
	       desc = "  " + pc + capitalize(inventory[count]->query_brief())
		  + " [idle" +
		  format_idle_time(inventory[count]->query_idle()) +
		  "]%^RESET%^";
	    } else {
	       desc =
		  "  " + pc + capitalize(inventory[count]->query_brief()) +
		  "%^RESET%^";
	    }
	 }
#ifdef LONG_ROOM_INV
	 text += desc + "\n";
      }
#else
	 if (!compacted_inv[desc]) {
	    compacted_inv[desc] = ( {
	       }
	    );
	 }
	 compacted_inv[desc] += ( {
	    inventory[count]}
	 );
      }

      if (compacted_inv && map_sizeof(compacted_inv)) {
	 string *keys;
	 int amount;

	 keys = map_indices(compacted_inv);

	 for (count = 0, size = sizeof(keys); count < size; count++) {
	    amount = sizeof(compacted_inv[keys[count]]);

	    if (amount == 1) {
	       text += keys[count];
	    } else {
	       text += keys[count] + " [x" + amount + "]";
	    }
	    text += "\n";
	 }
      }
#endif
   }
   return text;
}

void add_room_command(string command, string func) {
   if (!room_commands[command])
      room_commands += ([command:func]);
   else
      room_commands[command] = func;
}

void remove_room_command(string command) {
   room_commands[command] = nil;
}

string query_room_command(string command) {
   return room_commands[command];
}

/*-------------------------------------------------------------------
  sends a message to the room, designed specificly for non-living
  objects to communicate with the room
*/
void message_room(object originator, string str) {
   int i, sz;
   object *inventory;

   inventory = query_inventory();

   if (!inventory && sizeof(inventory) > 0) {
      return;
   }
   for (i = 0, sz = sizeof(inventory); i < sz; i++) {
      if (!inventory[i])
	 continue;
      if (originator != inventory[i]) {
	 if (inventory[i]->is_living()) {
	    inventory[i]->message(str);
	 }
	 inventory[i]->outside_message(str);
      }
   }
}

void tell_room(object originator, string str, varargs mixed obj ...) {
   int i;
   object *inventory;

   inventory = query_inventory();

   if (!inventory && sizeof(inventory) > 0) {
      return;
   }
   for (i = 0; i < sizeof(inventory); i++) {
      if (!inventory[i])
	 continue;
      if (originator != inventory[i] && member_array(inventory[i], obj) == -1) {
	 if (inventory[i]->is_living() &&
	    (!originator ||
	       !inventory[i]->query_ignored(originator->query_name()))) {
	    if (previous_object()->base_name() == "/cmds/player/say")
	       inventory[i]->message(capitalize(str), 1);
	    else
	       inventory[i]->message(capitalize(str));
	 }
	 inventory[i]->outside_message(capitalize(str));
      }
   }
}

string body_exit(object who, string dir) {
   int i;
   string error, lname, aname;
   object *inventory;
   object room;

   if (!query_exit(dir) && !query_hidden_exit(dir)) {
      write("You can't go " + dir + ".\n");
      return nil;
   }

   lname = who->query_proper_name();
   aname = lname;
   if (!lname) {
      /* Generic-named NPCs */
      lname = "The " + who->query_id();
      aname = "A " + who->query_id();
   }

   inventory = query_inventory();

   /* there is a normal exit */
   if (query_exit(dir)) {
      /* Is there a fake exit? */
      if (query_exit(dir)[0] == '#') {
	 return (query_exit(dir)[1..]);
      }
      for (i = 0; i < sizeof(inventory); i++) {
	 if (inventory[i]->is_blocking(dir)) {
	    /* We've got an object blocking the exit! */
	    if (!inventory[i]->do_block(who)) {
	       inventory[i]->other_action(inventory[i],
		  inventory[i]->query_block_action(), who, dir);
	       return nil;
	    }
	 }
      }
      event("body_leave", who);
      tell_room(who, lname + " leaves " + dir + ".\n");
      error = catch(who->move(query_exit(dir)));
      if (who->is_player())
	 last_exit = time();
   } else if (query_hidden_exit(dir)) {
      /* there is a hidden exit */
      if (query_hidden_exit(dir)[0] == '#') {
	 return query_hidden_exit(dir)[1..];
      }
      for (i = 0; i < sizeof(inventory); i++) {
	 if (inventory[i]->is_blocking(dir)) {
	    /* We've got a monster blocking the exit! */
	    if (inventory[i]->do_block(who)) {
	       inventory[i]->other_action(inventory[i],
		  inventory[i]->query_block_action(), who, dir);
	       return nil;
	    }
	 }
      }
      event("body_leave", who);
      tell_room(who, lname + " leaves " + dir + ".\n");
      error = catch(who->move(query_hidden_exit(dir)));
      if (who->is_player())
	 last_exit = time();
   }

   if (error) {
      if (query_wizard(who) == 1)
	 return "\nConstruction blocks your path.\n" + "Error: " + error;
      else
	 return "\nConstruction blocks your path.\n";
   }

   if (who->is_player() || who->is_possessed()) {
      PARSE_D->parse("look");

   }
   room = who->query_environment();
   room->event("body_enter", who);
   room->tell_room(who, aname + " enters.\n");
   return nil;
}

void destruct(void) {
   move_or_destruct_inventory();

   EVENT_D->unsubscribe_event("clean_up");
   ::destruct();
}

void event_clean_up(void) {
   int i;
   object *inventory;

   if (time() - last_exit < 60 * 15)
      return;

   inventory = query_inventory();
   for (i = 0; i < sizeof(inventory); i++) {
      if (!inventory[i])
	 continue;
      if (inventory[i]->is_player() || inventory[i]->is_possessed()
	 || inventory[i]->no_cleanup())
	 return;
   }

   destruct();
}

void upgraded() {
   ::upgraded();
   /*
    * special for rooms, ::upgraded() will only call
    * setup in clones, while blueprints of rooms are often used
    * and will also require setup.
    */
   if (clone_num() == 0)
      setup();
}

