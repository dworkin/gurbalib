#include "../../domain.h"

inherit DIR + "/lib/room";

int cmd_affixing(string str) {
   object smith;

   smith = this_object()->present("noki town smith");
   if (!smith) {
      write("The smith isn't here to ask.");
      return 1;
   }

   smith->respond("say I know how to affix "+
      "emeralds and topazes " +
      "to your equipment. If for some reason I can't do that, " +
      "I'll let you know. " +
      "But I'm always learning new things. " +
      "Feel free to check back another time to see if I've " +
      "learned to affix more things.");

   return 1;
}

int cmd_add(string str) {
   object smith, affix_this, target;
   string what, on_what;
   int coins, can_receive;

   smith = this_object()->present("noki town smith");
   if (!smith) {
      write("The smith isn't here to do that.");
      return 1;
   }

   if (empty_str(str)) {
      return 0;
   }

   if (smith->query_busy_right_now()) {
      smith->respond("say I'm busy right now. Gimme a minute.");
      return 1;
   }

   if (str == "affix" ||
         sscanf(str, "affix %s to %s", what, on_what) != 2) {
      smith->respond("say For instance, 'add affix emerald to crown'.");
      return 1;
   }

   affix_this = this_player()->present(what);
   target = this_player()->present(on_what);
   coins = this_player()->query_total_money();

   if (!affix_this || !target) {
      smith->respond("say Eh, come back when you have those.");
      return 1;
   }

   if (!function_object("can_receive_affix", target)) {
      smith->respond("grin");
      smith->respond("say That cannot have anything affixed to it.");
      return 1;
   }

   if (target->has_affix(what)) {
      smith->respond("say Well, it's already affixed with that.");
      return 1;
   }

   can_receive = target->can_receive_affix(what);

   if (can_receive == NOKICLIFFS_AFFIXES_NO) {
      smith->respond("say Hm, that's not possible. Sorry.");
      return 1;
   }

   if (can_receive == NOKICLIFFS_AFFIXES_FULL) {
      smith->respond("smile");
      smith->respond("say The " + on_what + " is full right now. " +
         "You know, though, I can remove some to make space.");
      return 1;
   }

   if (affix_this->query_value() > coins) {
      smith->respond("say You'd need " + coins + " ducats for me to that.");
      return 1;
   }

   if (target->is_worn() || target->is_wielded()) {
      smith->respond("chuckle");
      smith->respond("say I cannot work on it while you're using it.");
      return 1;
   }

   smith->add_affix_to_target(affix_this, target, affix_this->query_value(),
      this_player());
   return 1;
}

int cmd_remove(string str) {
   object smith, target;
   string what, on_what;
   int worth, coins;

   smith = this_object()->present("noki town smith");
   if (!smith) {
      write("The smith isn't here to do that.");
      return 1;
   }

   if (empty_str(str)) {
      return 0;
   }

   if (smith->query_busy_right_now()) {
      smith->respond("say I'm busy right now. Gimme a minute.");
      return 1;
   }

   if (strstr(str, "affix") > -1 &&
         sscanf(str, "affix %s from %s", what, on_what) != 2) {
      smith->respond("say For instance, 'remove affix emerald from crown'.");
      return 1;
   }

   if (sscanf(str, "affix %s from %s", what, on_what) != 2) {
      return 0;
   }

   target = this_player()->present(on_what);
   coins = this_player()->query_total_money();

   if (!target) {
      smith->respond("say Eh, come back when you have one.");
      return 1;
   }

   if (!target->has_affix(what)) {
      smith->respond("say Well, it's not affixed anyway.");
      return 1;
   }

   if (coins < 400) {
      smith->respond("say You'd need " + coins + " ducats for me to that.");
      return 1;
   }

   if (target->is_worn() || target->is_wielded()) {
      smith->respond("chuckle");
      smith->respond("say I cannot work on it while you're using it.");
      return 1;
   }

   smith->remove_affix_from_target(what, target, 400, this_player());
   return 1;
}

void setup(void) {
   set_short("Noki Town smithy");
   set_long("You are in the Noki Town smithy. The folks " +
      "who run this place are excellent smiths. They do not " +
      "create things to sell, but they can upgrade " +
      "your current adventuring gear. The sounds of metal " +
      "working in the back room fill the smithy's place. " +
      "If the smith is about, he can affix certain items to " +
      "equipment which imbues the equipment with special power. " +
      "\n\tTo find out what the smithy knows, type 'affixing'." +
      "\n\tTo affix an item, type " +
      "'affix add <item> to <affixable>'. " +
      "\n\tTo remove an item, type " +
      "'remove affix <item> from <affixable>'." +
      "\n\tTo use an affixed item, type " +
      "'touch <item> on <affixable'.");

   set_exits(([ "south" : DIR + "/rooms/town/square_north.c" ]));

   set_objects(NOKICLIFFS_TOWN_SMITH);

   add_action("cmd_affixing", "affixing");
   add_action("cmd_add", "add");
   add_action("cmd_remove", "remove");
}

