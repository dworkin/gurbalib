#include "../domain.h"

inherit obj "/std/object";
inherit timer "/std/body/heart_beat";

#define INTERVAL 8
static int count;
static object guard;

void remove_corpse(void) {
   object *inv;
   int i, dim;

   inv = this_object()->query_environment()->query_inventory();
   for (i = 0, dim = sizeof(inv); i < dim; i++) {
      if (inv[i]->query_id() == "corpse") {
         inv[i]->destruct();
      }
   }
}

void summon_guard(void) {
   object env;

   remove_corpse();
   env = this_object()->query_environment();

   if (env) {
      count = 0;
      if (!find_object(NOKICLIFFS_BRAIN_GUARD)) {
         compile_object(NOKICLIFFS_BRAIN_GUARD);
      }
      if (!guard) {
         guard = clone_object(NOKICLIFFS_BRAIN_GUARD);
         guard->setup();
      }
      if (guard->query_environment() != env) {
         guard->move(env);
         env->tell_room(this_object(),
            "The brain's guardian " +
            "appears in a puff " +
            "of smoke.");
         guard->announce_yourself();
      } else {
         if (!random(3)) {
            guard->random_act_of_menace();
         }
      }
   }
}

void setup(void) {
   obj::set_id("brain");
   obj::add_id("jar");
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

void create(void) {
   obj::create();
   timer::create();
}

string query_Name(void) {
   return "brain";
}

string query_name(void) {
   return "brain";
}

void event_heart_beat(void) {
   object env;
   env = this_object()->query_environment();
   if (env) {
      if (++count > INTERVAL) {
         summon_guard();
         count = 0;
      }
   }
}

void outside_message(string str) {
   object env;
   env = this_object()->query_environment();
   str = ANSI_D->strip_colors(str);

   if (sscanf(str, "%s enters.")) {
      env->tell_room(this_object(), "The brain " +
         "ripples with some mystic blue energy.");
      summon_guard();
   }
   if (str == "Guard falls to the ground...dead.") {
      if (env) {
         env->tell_room(this_object(), "The brain " +
            "turns green and then back to grey.");
         count = 0;
      }
   }
}
