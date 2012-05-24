inherit ROOM;

void setup(void) {
   add_area("Gurba");
   set_brief("Gelmir Road");
   set_long("You are standing on a well travelled road, directly east of " +
      "the town square. To the north you have the entrance to the " +
      "'Thick Beard' pub. Further to the east will get you to the Fighters " +
      "Guild.");
   set_exits(([
      "west" : "/domains/gurba/town_square",
      "east" : "/domains/gurba/rooms/gelmir2",
   ]));

   add_item("road", "path", "floor", "street", "The road is in good " +
      "condition. None of the rocks used to pave the road have lost " +
      "their square shape, or are chipped in any way.");
   add_item("pub", "bar", "inn", "The pub was earlier called 'Yellow " +
      "Hedge', but quickly changed name when the barkeep quit shaving.");
}
