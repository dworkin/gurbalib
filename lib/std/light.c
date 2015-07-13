inherit obj "/std/object";

int fuel, lit;

int set_fuel(int x) {
   fuel = x;
}

int query_fuel(void) {
   if (fuel < 0) {
      return 0;
   }
   return fuel;
}

int query_lit(void) {
   return lit;
}

static int light(void) {
   EVENT_D->subscribe_event("heart_beat");
   lit = 1;
   write("You light the " + this_object()->query_id() + ".\n");
   this_player()->query_environment()->tell_room(this_player(), 
      this_player()->query_Name() + " lights the " + 
      this_object()->query_id() + ".\n");
   return 1;
}

static int extinguish(void) {
   lit = 0;
   write("You extinguish the " + this_object()->query_id() + ".\n");
   this_player()->query_environment()->tell_room(this_player(), 
      this_player()->query_Name() + " extinguishes the " + 
      this_object()->query_id() + ".\n");
   return 1;
}

private int burn_fuel(void) {
   object room;

   if (!query_lit()) {
      return 0;
   }

   if (--fuel < 5) {
      room = query_environment();
      if (room->is_living()) {
         write("Your " + query_id() + " dims.\n");
      }
   }

   if (fuel < 1) {
      room = query_environment();
      if (room->is_living()) {
         write("Your " + query_id() + " goes out.\n");
         say(room->query_Name() + "'s " + query_id() + " goes out.\n");
      } else {
         room->message_room(room, "The " + query_id() + " goes out.\n");
      }

      lit = 0;
      EVENT_D->unsubscribe_event("heart_beat");
   }

   return 1;
}

private string lit_or_unlit(void) {
   if (query_lit()) {
      return "lit";
   }

   return "unlit";
}

string query_short(void) {
   string str;

   str = ::query_short() + " [" + lit_or_unlit() + "]";

   if (query_fuel() < 20) {
      str += " [very low on fuel]";
   }

   return str;
}

string query_long(void) {
   string str;

   str = ::query_long() + "\nIt is " + lit_or_unlit() + ".";
   if (query_fuel() < 20) {
      str += "\nIt is very low on fuel.";
   }

   return str;
}

void event_heart_beat(void) {
   burn_fuel();
}

string query_name(void) {
   return query_id();
}

private void light_usage(void) {
   string *lines;

   lines = ({ "Usage: light [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Turn on, or light the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tlight torch" });
   lines += ({ "\tlight lamp" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, extinguish, identify, list, listen, look, " +
      "search, sell, value" });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who"
         });
   }

   this_player()->more(lines);
}

private void extinguish_usage(void) {
   string *lines;

   lines = ({ "Usage: extinguish [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "Turn off, or extinguish the specified object." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\textinguish torch" });
   lines += ({ "\textinguish lamp" });
   lines += ({ "See also:" });
   lines += ({ "\tbuy, identify, light, list, listen, look, " +
      "search, sell, value" });

   if (query_wizard(this_player())) {
      lines += ({ "\tlast, locate, mudlist, possess, rwho, snoop, where, who"
         });
   }

   this_player()->more(lines);
}

int do_light(string str) {
   if (empty_str(str)) {
      light_usage();
      return 1;
   }
   if (sscanf(str, "-%s", str)) {
      light_usage();
      return 1;
   }
   if (lowercase(str) != lowercase(query_id())) {
      return 0;
   }
   if (query_lit()) {
      write("Your " + str + " is already lit.");
      return 1;
   }
   if (fuel < 1) {
      write("Your " + str + " is out of fuel.");
      return 1;
   }

   return light();
}


int do_extinguish(string str) {
   if (empty_str(str)) {
      extinguish_usage();
      return 1;
   }
   if (sscanf(str, "-%s", str)) {
      extinguish_usage();
      return 1;
   }
   if (lowercase(str) != lowercase(query_id())) {
      return 0;
   }
   if (!query_lit()) {
      write("Your " + str + " is not lit.");
      return 1;
   }

   return extinguish();
}

void create(void) {
   obj::create();

   set_fuel(1000);
   add_action("do_light", "light");
   add_action("do_extinguish", "extinguish");
}

