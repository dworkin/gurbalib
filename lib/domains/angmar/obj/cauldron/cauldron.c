#include "../../domain.h"

inherit "/std/container";
inherit "/std/modules/m_triggers";

int check_ingredients(void) {
   int x;

   x = this_object()->present("dead fish") &&
      this_object()->present("slimy mushroom") &&
      this_object()->present("rat skeleton") &&
      this_object()->present("corn cob") &&
      this_object()->present("angmars recipe");

   if (CORPSE_GETTABLE) {
      x = x && this_object()->present("corpse");
   }

   return x;
}

private void clean_out_from_cauldron(string what) {
   object obj;

   obj = this_object()->present(what);
   if (obj) {
      obj->destruct();
   }
}

void clean_cauldron(void) {
   clean_out_from_cauldron("dead fish");
   clean_out_from_cauldron("slimy mushroom");
   clean_out_from_cauldron("rat skeleton");
   clean_out_from_cauldron("corn cob");
   clean_out_from_cauldron("angmars recipe");
   if (CORPSE_GETTABLE) {
      clean_out_from_cauldron("corpse");
   }
}

void reward(object player) {
   object coins, ring;
   int level;

   if (!player || !this_object()->query_environment()->present(player->query_name())) {
      return;
   }

   if (check_ingredients()) {
      player->simple_action("As $N $vutter the magic words steam comes out of the cauldron!");
      level = player->query_level();

      if (level < 12) {
         coins = clone_object(DOMAINS_DIR + "/required/objects/coin.c");
         coins->set_currency("ducat");
         coins->set_amount(level * (1 + random(100)) + random(100));
         coins->move(this_object());
         clean_cauldron();

         return;
      }

      ring = clone_object(DIR + "/obj/quest_rings/silver_ring.c");
      ring->setup();
      ring->move(this_object());
      clean_cauldron();

      return;
   }

   player->simple_action("As $N utters the magic words nothing happens.");
}

void respond(string str) {
   object player;

   player = this_object()->query_environment()->present(lowercase(str));
   if (!player) {
      return;
   }

   call_out("reward", 1, player);
}

void setup(void) {
   set_id("cauldron");
   set_adj("big");
   set_short("A big cauldron");
   set_long("A big black iron cauldron. I wonder what it has been used for?");
   set_gettable(0);

   add_pattern("%s says: Kashmirak gorondolum.\n", "$1");
}
