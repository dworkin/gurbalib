#include "../domain.h"

inherit "/std/room";

void setup(void) {
   set_short("Chez Mario's Kitchen");
   set_long("This is the kitchen, the place where Mario's chef makes " +
      "all the food. There is a stove, a sink, some shelves with " +
      "different ingredients, and a box containing knives, forks and " +
      "spoons. The room is kept quite clean.");
   set_exits(([
      "south" : DIR + "/rooms/restaurant",
   ]));

   add_item("stove", "It is an old iron wood stove that could use some " +
      "brushing up, but it serves its purpose. There is a hole at the " +
      "bottom for inserting wood.");
   add_item("shelves", "ingredients", "shelf", "ingredient",
      "Lined along the shelves stand several bottles, jars and cans " +
      "holding everything from pasta to seasoning.");
   add_item("box", "The box is a small wooden box that holds the " +
      "eating-utensils and a couple of napkins.");
   add_item("sink", "A normal sink for cleaning and washing up.");
}
