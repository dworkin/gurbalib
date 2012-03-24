inherit ROOM;

void setup(void) {
   add_area("Gurba");
   set_brief("%^GREEN%^Gurba Town Square%^RESET%^");
   set_long("This is the natural meeting place in the town of Gurba. In " +
      "the center of the square is a large statue of the city's founder. " +
      "It's a breathtaking sight.  Hanging next to the statue is a " +
      "large, ancient-looking bell.");

   set_exits(([
      "west" : "/domains/gurba/rooms/market1",
      "east" : "/domains/gurba/rooms/gelmir1",
   ]));

   add_item("statue", "A pretty large and well crafted statue of a " +
      "small dwarf. It is decorated with fine jewels and gold, and at " +
      "the base is a small plaque.");
   add_item("jewels", "jewel", "Upon closer inspection you see that all " +
      "of the jewels are cheap glass imitations of the real thing.");
   add_item("gold", "The gold isn't especially impressive. It's just " +
      "painted onto the solid rock the statue is crafted from.");
   add_item("plaque", "The plaque says: Fudge, where are you now?");
   add_item("bell", "The bell looks extremely old.  It is made of bronze " +
      "and has indecipherable writing and patterns on its bottom edge.  " +
      "It might be possible to ring it.");

   set_objects(([
      "/domains/gurba/objects/main_board" : 1,
   ]));

   add_room_command("ring", "ring_bell");
}

int ring_bell(string arg) {
   if (arg == "bell") {
      this_player()->simple_action("$N $vring the bell.  A deep, sonorous " +
         "toll echoes across the square.");
   } else
      write("Ring what?");
}
