#include "../../domain.h"

inherit "/std/room";

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("The forge");
   set_long("You are in Angmar's forge.");

   set_objects(DIR + "/monsters/smith.c");

   add_exit("east", CASTLE_ROOMS + "/inside.c");

   add_item("forge", "There is little left of the forge.");

   add_action("cost_cmd", "cost");
   add_action("show_cmd", "show");
}

int cost_cmd(string str) {
   object item, smith;
   int val;

   if (empty_str(str)) {
      return 0;
   }

   item = this_player()->present(str);
   if (!item) {
      write("No such item here.");
      return 1;
   }

   val = item->query_value() / 5;
   if (val < 30) {
      val = 30;
   }
   if (val > 800) {
      val = 800;
   }

   write("The smith would take " + val + " ducats to value that.");

   smith = present("angmar's smith");
   if (!smith) {
      write("Unfortunately, the smith isn't here right now.");
   }

   return 1;
}

int show_cmd(string str) {
   object item, smith;
   int ac, wc, val, cost;

   if (empty_str(str)) {
      return 0;
   }

   item = this_player()->present(str);
   if (!item) {
      write("No such item here.");
      return 1;
   }

   if (function_object("query_ac", item)) {
      ac = item->query_ac();
   }

   if (function_object("query_weapon_class", item)) {
      wc = item->query_weapon_class();
   }

   if (!ac && !wc) {
      write("The smith is not interested in such things.");
      return 1;
   }

   cost = item->query_value() / 5;
   if (cost < 30) {
      cost = 30;
   }
   if (cost > 800) {
      cost = 800;
   }

   if (cost > this_player()->query_total_money()) {
      write("You don't have enough money to pay the smith.");
      return 1;
   }

   smith = present("angmar's smith");
   if (!smith) {
      write("Unfortunately, the smith isn't here right now.");
   }

   this_player()->simple_action("$N $vshow something to the smith.");
   this_player()->add_money("ducat", -cost);

   if (item->is_id("doomsgiver")) {
      smith->respond("nod");
      smith->respond("I recognize this weapon. It was made by Angmar himself.");
      smith->respond("emote seems to fall in deep thoughts and shudders at some memory. " +
         "After a while he looks up.");
      smith->respond("say Anyway, it is the most powerful weapon I know of, " +
         "but it is only used by evil persons.");
      return 1;
   }

   if (val > 20) {
      smith->respond("gasp");
      smith->respond("say Where did you get this? The knowledge to make such fine "+
         "handicraft is long forgotten in this world, I'm sorry to say. " +
         (wc > 0 ? "It is an extremely powerful weapon! Use it with care." :
            "It is an extremely good armor! Don't lose it!"));
      return 1;
   }

   if (val > 17) {
      smith->respond("eyebrow");
      smith->respond("say I'm impressed! It would be hard to find one better. " +
         "It should serve you well in your future battles.");
      return 1;
   }

   if (val > 13) {
      smith->respond("emote nods appreciatively.");
      smith->respond("A very fine " +
         (wc > 0 ? "weapon" : "armor") + " indeed. " +
         "It has been used in many battles, I can see, " +
         "but it is still fully functional.");
      return 1;
   }

   if (val > 9) {
      smith->respond("emote examines it.");
      smith->respond("say It's good enough. It's not of the very "+
         "best quality though, I wouldn't try to do battle with any " +
         "great warrior with it if I were you.");
      return 1;
   }

   if (val > 5) {
      smith->respond("emote frowns.");
      smith->respond("say I hope you didn't pay much for this? You " +
         "should get yourself a better one. You could easily get killed " +
         "if you should happen to run into any big monsters, you know.");
      return 1;
   }

   smith->respond("emote sighs and shakes his head.");
   smith->respond("say Cheap crap. Hardly worth anything. " +
      (wc > 0 ? "I doubt you could even kill an orc with it." :
      "It probably couldn't even stop the blow from a small knife."));

   return 1;
}
