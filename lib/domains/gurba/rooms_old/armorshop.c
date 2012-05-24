inherit ROOM;

void setup(void) {
   set_brief("The armor shop");
   set_long("Here is the armor shop, a small plaque hangs on a wall next " +
      "to the entrance, all sorts of armor and shields are hung on the " +
      "walls. Timoth the centaur is running the show here. ");
   set_exits(([
      "north" : "/domains/gurba/rooms/market2",
   ]));

   add_item("armor", "armors", "shields", "shield",
      "Shields and armor for all races.");
   add_item("plaque", "The plaque says: We rather be safe than sorry!");
   set_objects(([]));

}

void do_listen(object player) {
   write("You can hear the tail of Timoth the centaur swapping flies.");
}
