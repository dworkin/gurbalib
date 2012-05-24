inherit ROOM;

void setup(void) {
   set_brief("Chez Mario");
   set_long("This is the kitchen, the place where Mario makes all the " +
      "food. There is a stove, a sink, some shelves with different " +
      "ingredients, a book that says 'cooking made easy' and a box " +
      "containing knives, forks and spoons. He keps the place tidy.");

   set_exits(([
      "north" : "/domains/gurba/rooms/restaurant",
   ]));

   add_item("stove", "It is an old iron stove that could need some " +
      "brushing up, but it serves its purpose. There is a hole at the " +
      "bottom for entering wood.");
   add_item("shelves", "ingredients", "shelf", "ingredient",
      "Lined along the shelves stand several bottles, jars and cans " +
      "holding everything from pasta to seasoning.");
   add_item("box", "The box is a small wooden box that holds the " +
      "eating-utensiles and a couple of napkins.");
   add_item("sink", "A normal sink for cleaning and washing up.");
   add_item("door", "A normal wooden door, leading back to the restaurant.");
}

void do_listen(object player) {
   write("You can hear Mario humming from the resturant.");
}
