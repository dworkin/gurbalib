#include "../../domain.h"

inherit "/std/room";

static object is_waiting_for;
static int co_handle;
string *set1, *set2, *set3;
static mapping passwords;

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("The entrance to Angmar's treasury");
   set_long("This is the entrance to Angmar's treasury. Many are the tales " +
      "about his hidden treasures. So far, nobody has been able to " +
      "enter. Maybe you will be the first one? " +
      "There are twin iron doors to the north. They are closed. " +
      "You see reliefs of three rings on them, which is a clue for how to "+
      "open the doors.");

   set_objects(
      DIR + "/monsters/thief.c"
   );

   add_exit("south", CASTLE_ROOMS + "/midstairs.c");

   add_action("open_cmd", "open");

   set1 = ({
      "tarantor",
      "hashnuk",
      "gothnir",
      "hurfurin",
      "alannen",
      "rhastul"
   });

   set2 = ({
      "osibilum",
      "shiryllis",
      "fornor",
      "es",
      "eth",
      "sureth"
   });

   set3 = ({
      "brupp",
      "hades",
      "grukk",
      "elte",
      "connon",
      "benambra"
   });

   passwords = ([]);
   is_waiting_for = nil;
}

string generate_password(object for_player) {
   string password;

   password = random_element(set1) + " " +
         random_element(set2) + " " +
         random_element(set3);

   passwords[for_player->query_name()] = password;

   return password;
}

void destroy_rings(object intruder) {
   object r1, r2, r3;
   object *inventory;
   int i, sz, x, y, z;

   inventory = intruder->query_inventory();
   x = 0;
   y = 0;
   z = 0;
   sz = sizeof(inventory);
   for (i = 0; i < sz; i++) {
      if (inventory[i]->is_id("trlock1")) {
         x = 1;
         r1 = inventory[i];
         continue;
      }
      if (inventory[i]->is_id("trlock2")) {
         y = 1;
         r2 = inventory[i];
         continue;
      }
      if (inventory[i]->is_id("trlock3")) {
         z = 1;
         r3 = inventory[i];
      }
   }

   if (x == 1 && y == 1 && z == 1) {
      r1->destruct();
      r2->destruct();
      r3->destruct();
   }
}

int has_rings(object intruder) {
   return intruder->present("trlock1") && intruder->present("trlock2") && intruder->present("trlock3");
}

int correct_password(string intruder_name, string intruder_says) {
   return passwords[intruder_name] &&
          passwords[intruder_name] == lowercase(intruder_says);
}

void stop_waiting(void) {
   remove_call_out(co_handle);
   is_waiting_for = nil;

   tell_room(this_object(), "The three rings on the twin iron doors stop glowing.");
}

void ask_for_password(void) {
   tell_room(this_object(), "A ghostly blue face appears on the twin iron " +
      "doors and says: 'say the password'.");

   co_handle = call_out("stop_waiting", 30);
}

void handle_intruder(object intruder) {
   is_waiting_for = intruder;
   destroy_rings(intruder);

   intruder->simple_action("The three rings on the twin iron doors start to " +
      "glow with a soft blue light.");
   intruder->message("The three rings in your pocket disappear.");

   call_out("ask_for_password", 3);
}

void move_intruder_to_treasury(object intruder) {
   stop_waiting();

   if (!intruder || !present(intruder->query_name())) {
      return ;
   }

   intruder->simple_action("As $N $vutter the password to Angmar's " +
      "treasury the twin iron doors open slowly and without " +
      "a sound; $n $vwalk through and the doors close.");
   intruder->move(CASTLE_ROOMS + "/treasury.c");
   intruder->query_environment()->prepare_treasury();
   intruder->do_look(intruder->query_environment());
   intruder->add_completed_quest(ANGMAR_TREASURY_QUEST);
}

void tell_room(object originator, string str, varargs mixed obj ...) {
   object intruder;
   string intruder_name, intruder_says, s;

   s = ANSI_D->strip_colors(str);

   if (sscanf(s, "%s enters.\n", intruder_name) == 1) {
      intruder = present(lowercase(intruder_name));
      if (!intruder->is_quest_completed(ANGMAR_TREASURY_QUEST)) {
         if (is_waiting_for && intruder != is_waiting_for && has_rings(intruder)) {
            intruder->message("Come back in a minute to attempt the quest.");
         } else {
            handle_intruder(intruder);
         }
      }
   }

   if (sscanf(s, "%s says: %s.\n", intruder_name, intruder_says) == 2) {
      intruder_name = lowercase(intruder_name);
      intruder = present(intruder_name);
      if (!intruder->is_quest_completed(ANGMAR_TREASURY_QUEST)) {
         if (is_waiting_for == intruder && correct_password(intruder_name, intruder_says)) {
            passwords[intruder_name] = nil;
            call_out("move_intruder_to_treasury", 2, intruder);
         } else if (is_waiting_for != intruder && correct_password(intruder_name, intruder_says)) {
            intruder->message("Not yet. Come back in a minute to attempt the quest.");
         }
      }
   }

   ::tell_room(originator, str, obj);
}

int open_cmd(string str) {
   if (str && (str == "doors" || str == "iron doors" ||
         str == "twin doors" || str == "twin iron doors")) {
      this_player()->increase_hp(-5);
      this_player()->simple_action("$N $vtry to open the twin iron doors " +
         "and get hit with a blue flash and $n $vhowl in pain.");
      return 1;
   }

   return 0;
}
