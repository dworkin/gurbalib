inherit ROOM;

void setup(void) {
   set_brief("%^BLUE%^Chez Mario%^RESET%^");
   set_long("This is no five star restaurant, but it is indeed a nice " +
      "eatingplace, with a personal and charming touch to it. The place " +
      "has six tables, a small stage and a bar with a door behind it. " +
      "Mario himself is speeding around cleaning tables, humming rapidly " +
      "some piece of music and having a cigarette at the same time. " +
      "'Please, have a seat' he says when you enter. ");

   set_exits(([
      "north" : "/domains/gurba/rooms/market3",
      "south" : "/domains/gurba/rooms/restaurant2",
   ]));

   add_item("tables", "table", "Each of the six wooden tables has four " +
      "chairs, and is clad in a big red'n'white chequered tablecloth.");
   add_item("bar", "At the opposite side of the entrance is a bar, rising " +
      "one and a half meters. In front of the bar are five wooden " +
      "barstooles. Behind the bar are several shelves of beverage. There " +
      "is a gap at the righthand end of the bar leading to a door, " +
      "probably to the kitchen.");
   add_item("stage", "A small stage is at the west wall, just big enough " +
      "to hold a band of four.");
   add_item("tablecloth", "cloth", "It seems like any other tablecloth");
   add_item("stooles", "stoole", "barstool", "barstooles",
      "Tall typical barstooles");
   add_item("door", "A normal wooden door, leading to the kitchen");
}

void do_listen(object player) {
   write("You can hear Mario humming, and something sizzling in the " +
      "kitchen, probably lunch.");
}
