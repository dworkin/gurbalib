#include "../domain.h"

inherit "/std/container";
inherit "/std/modules/m_openable";
inherit MONEY_MAKER;

#define COIN_AMT (10 * (random(5) + 2))
#define TURNS ({ "left", "right", "left" })

static int turns;

int can_open(object thief) {
   return turns == sizeof(TURNS);
}

int query_turns(void) {
   return turns;
}

static void add_coins(void) {
   object royals, crowns;

   make_money("royal", COIN_AMT)->move(this_object());
   make_money("crown", COIN_AMT)->move(this_object());
}

static void add_actions(void) {
   add_action("turn_dial_cmd", "turn");
   add_action("spin_dial_cmd", "spin");
}

int do_close(object thief) {
   int s;
   s = ::do_close(thief);
   if (s == 1 && open_state == 0) {
      this_environment()->tell_room(nil, + "The vault's lock " +
         "resets.");
      turns = 0;
   }
}

void notify_failed_turn(object thief) {
}

void notify_no_stethoscope(object thief) {
}

void notify_good_turn(object thief, object stethoscope) {
}

void notify_bad_turn(object thief, object stethoscope) {
}

void notify_unlock(object thief, object stethoscope) {
}

int spin_dial_cmd(string str) {
   if (empty_str(str)) {
      write("Spin what?");
      return 1;
   }

   if (str == "dial") {
      this_player()->targeted_action("$N $vspin the dial, " +
         "resetting the lock.", this_player());
      return 1;
   }

   return 0;
}

int turn_dial_cmd(string str) {
   object *inv;
   object  stethoscope;
   int     i, dim, s;
   string  dir;

   if (empty_str(str)) {
      write("Left or right?");
      return 1;
   }

   inv = this_player()->query_inventory();
   dim = sizeof(inv);
   for (i = 0; i < dim; i++) {
      if (inv[i]->is_id("stethoscope")) {
         stethoscope = inv[i];
         break;
      }
   }

   s = sscanf(str, "dial %s", dir);

   if (s != 1 || (dir != "left" && dir != "right")) {
      write("Turn dial left or turn dial right.");
      notify_failed_turn(this_player());
      return 1;
   }

   if (!stethoscope) {
      this_player()->targeted_action("$N $vturn the dial " +
         "like an amatuer.", this_player());
      notify_no_stethoscope(this_player());
      return 1;
   }

   this_player()->targeted_action("$N $vturn the dial " +
      "on the safe to the " +
      dir + " while using a stethoscope to listen " +
      "to the lock.", this_player());
   notify_good_turn(this_player(), stethoscope);

   if (turns == sizeof(TURNS)) {
      turns = 0;
   }

   if (TURNS[turns] == dir) {
      write("You hear an encouraging click.");
      turns++;
      if (turns == sizeof(TURNS)) {
         write("You hear the " +
            "lock on the safe switch into the open " +
            "position.");
         notify_unlock(this_player(), stethoscope);
      }
   } else {
      write("You hear nothing but the sound of failure.");
      turns = 0;
      notify_bad_turn(this_player(), stethoscope);
   }

   return 1;
}

void create(void) {
   ::create();
   turns = 0;
   set_gettable(0);
   set_weight(5000);
   set_value(0);
   add_actions();
   add_coins();
}
