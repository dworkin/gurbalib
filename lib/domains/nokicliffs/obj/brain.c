#include "../domain.h"

inherit obj "/std/object";
inherit timer "/std/body/heart_beat";

#define INTERVAL 15
static int count;
static object guard;

void setup() {
   obj::set_id("brain");
   obj::set_short("A brain in a jar of mystic fluid");
   obj::set_long("A large brain suspended in a jar of mystic " +
      "fluid. It has no apparent body but is definitely " +
      "alive. At least the grey matter is, almost " +
      "imperceptibly, pulsating within the fluid.");
   obj::set_gettable(0);
   obj::set_weight(1);
   obj::set_value(0);
   count = 0;
}

void create() {
   obj::create();
   timer::create();
}

string query_Name() {
   return "brain";
}

string query_name() {
   return "brain";
}

void remove_corpse() {
	object *inv;
	int i, dim;
	inv = this_object()->query_environment()->query_inventory();
	for (i = 0, dim = sizeof(inv); i < dim; i++) {
		if (inv[i]->query_id() == "corpse") {
			inv[i]->destruct();
		}
	}
}

void summon_guard() {
   object env;
	remove_corpse();
   env = this_object()->query_environment();
   if (env) {
      if (env->present("guard")) {
			guard->respond("growl");
         return;
      }
      if (!find_object(NOKICLIFFS_BRAIN_GUARD)) {
         compile_object(NOKICLIFFS_BRAIN_GUARD);
      }
      if (!guard) {
         guard = clone_object(NOKICLIFFS_BRAIN_GUARD);
			guard->setup();
      }
      guard->move(env);
      env->tell_room(this_object(), "The brain's guardian " +
         "appears in a puff of smoke.");
		guard->announce_yourself();
   }
}

void event_heart_beat() {
   object env;
   env = this_object()->query_environment();
   if (env) {
      if (++count > INTERVAL) {
			summon_guard();
			count = 0;
      }
   }
}

void die() {
   this_object()->query_environment()->tell_room(nil,
      "The jar explodes into a shower of sparks!");
   this_object()->destruct();
}

