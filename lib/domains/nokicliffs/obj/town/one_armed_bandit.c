#include "../../domain.h"

inherit "/std/object";

string *possible_slots;
mapping special_slots;
string *wheel_sounds;
static int being_played;
static string *results;

private void roll_wheel(string slot, string wheel_sound) {
   TELL_ROOM(this_object(), " ... click ... " + slot + "\n" + wheel_sound);
}

void analyse_results(object player) {
   if (player->query_environment() == this_object()->query_environment()) {
      player->simple_action("$N $vfeel swindled.");
   } else {
      TELL_ROOM(this_object(), "Game Over.");
   }
   being_played = FALSE;
}

void third_wheel(object player) {
   string slot, wheel_sound;

   wheel_sound = random_element(wheel_sounds);
   slot = random_element(possible_slots);
   results[2] = slot;

   TELL_ROOM(this_object(), " ... click ... " + slot);

   analyse_results(player);
}

void second_wheel(object player) {
   string slot, wheel_sound;

   wheel_sound = random_element(wheel_sounds);
   slot = random_element(possible_slots);
   results[1] = slot;

   roll_wheel(slot, wheel_sound);

   call_out("third_wheel", 2, player);
}

void first_wheel(object player) {
   string slot, wheel_sound;

   wheel_sound = random_element(wheel_sounds);
   slot = random_element(possible_slots);
   results[0] = slot;

   roll_wheel(slot, wheel_sound);

   call_out("second_wheel", 2, player);
}

void start_playing(object player) {
   string wheel_sound;

   wheel_sound = random_element(wheel_sounds);
   TELL_ROOM(this_object(), wheel_sound);
   call_out("first_wheel", 1, player);
}

void play_slots(object player) {
   being_played = TRUE;
   player->add_money("ducat", -5);
   player->simple_action("$N $vdrop 5 ducats into the one-armed " +
      "bandit and pulls the arm...\nbrrrrp ching... the wheels " +
      "start spinning.");
   call_out("start_playing", 1, player);
}

int cmd_play_slots(string str) {
   if (empty_str(str) || str != "slots") {
      this_player()->simple_action("$N $vlook for a game to play.",
            this_player());
      return 1;
   }

   if (being_played) {
      this_player()->simple_action("$N $vwait to play slots.",
            this_player());
      return 1;
   }

   if (this_player()->query_total_money() < 5) {
      this_player()->simple_action("$N $vwant to play slots but " +
         "cannot afford to play the game.", this_player());
      return 1;
   }

   play_slots(this_player());

   return 1;
}

int cmd_reset_slots(string str) {
   being_played = FALSE;
   write("You reset the slot machine.");
   return 1;
}

void setup(void) {
   set_id("one-armed bandit");
   add_ids("slot machine");
   set_short("A one-armed bandit");
   set_long("The one-armed bandit is by far the favorite " +
      "game to play in all of Noki Town. To play the game " +
      "simply type 'play slots'.");
   set_gettable(0);

   possible_slots = ({
      "rejuvination potion",
      "troll",
      "orc shaman",
      "pixie",
      "42",
      "Leo",
      "crossed swords",
      "shield",
      "sea shell",
      "diamond",
      "emerald",
      "sapphire"
   });

   wheel_sounds = ({
      "beep boop beep",
      "ding dong",
      "boop ditty boop"
   });

   results = allocate(3);
   special_slots = ([ ]);
   special_slots["diamond"] = 10;
   special_slots["42"] = 42;

   add_action("cmd_play_slots", "play");
   add_action("cmd_reset_slots", "reset");
}