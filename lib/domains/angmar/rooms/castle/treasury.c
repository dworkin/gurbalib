#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("Angmar's treasury");
   set_long("You are in Angmar's treasury.");

   add_exit("south", "#go_south");
}

void go_south(void) {
   this_player()->simple_action("$N triumphantly $vopen the " +
      "twin iron doors and $vgo south out of Angmar's treasury.");
   this_player()->move(CASTLE_ROOMS + "/treasury_entrance.c");
   this_player()->query_environment()->tell_room(this_player(),
         "The twin iron doors to Angmar's treasury swing open " +
         "and " + this_player()->query_Name() + " arrives. " +
         "The the twin iron doors close.");
   this_player()->do_look(this_player()->query_environment());
}

private void add_treasure(string id, string file_name) {
   object ob;

   ob = present(id);
   if (!ob) {
      ob = clone_object(file_name);
      ob->setup();
      ob->move(this_object());
   }
}

void prepare_treasury(void) {
   object obj;

   obj = present("coins");
   if (!obj) {
      obj = clone_object(DOMAINS_DIR + "/required/objects/coin.c");
      obj->set_currency("crown");
      obj->set_amount(5);
      obj->move(this_object());
   }

   add_treasure("sapphire", DIR + "/obj/treasury/sapphire.c");
   add_treasure("diamond", DIR + "/obj/treasury/diamond.c");
   add_treasure("heavy spear", DIR + "/obj/weapons/heavy_spear.c");
   add_treasure("ancient sword", DIR + "/obj/weapons/ancient_sword.c");
}
