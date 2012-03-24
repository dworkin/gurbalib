inherit ROOM;

void setup(void) {
   add_area("Gurba");
   set_brief("%^MAGENTA%^Market Boulevard%^RESET%^");
   set_long("This is beginning of the market street in Gurba. Here, you " +
      "can find all things that money can buy. To the east you see the " +
      "town square. To the north is Adams Boutique of Curiosity, south " +
      "lies Fridas Floristeria.");

   set_exits(([
      "west" : "/domains/gurba/rooms/market2",
      "east" : "/domains/gurba/town_square",
      "north" : "/domains/gurba/rooms/adams",
      "south" : "/domains/gurba/rooms/florist",
   ]));

   add_item("road", "The road here is paved with cobblestones due to all " +
      "the traffic that runs through here.");
   add_item("cobblestone", "cobblestones", "cobble", "stones",
      "The stones are small quadratic stones laid down side by side.");
}

void do_listen(object player) {
   write("You hear the bustling sound of trade, money, haggling and " +
      "merchants having it off at each other.");
}
