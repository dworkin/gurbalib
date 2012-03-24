inherit ROOM;

void setup(void) {
   add_area("Gurba");
   add_area("GurbaSquare");
   add_area("GurbaOutdoor");

   set_brief("Gurba Town Square Center");
   set_long("The center of the Gurba Town Square provides a natural " +
      "meeting place in the heart of the town. The square is large " +
      "and open, and paved with aging red brick. It is extremely busy " +
      "at all times of day and night. People bustle around in groups, " +
      "talking and laughing. In the center of the square is a large " +
      "gilt statue of the city's founder. It's a breathtaking sight. " +
      "Hanging next to the statue is a large, ancient-looking bell.");

   set_exits(([
      "north" : "/domains/gurba/rooms/square_north",
      "south" : "/domains/gurba/rooms/square_south",
      "east" : "/domains/gurba/rooms/square_east",
      "west" : "/domains/gurba/rooms/square_west",
      "northeast" : "/domains/gurba/rooms/square_northeast",
      "northwest" : "/domains/gurba/rooms/square_northwest",
      "southeast" : "/domains/gurba/rooms/square_southeast",
      "southwest" : "/domains/gurba/rooms/square_southwest",
   ]));

   add_item("statue", "A large and well-crafted statue of a dwarf. It " +
      "is decorated with glittering jewels and gold, and at the base " +
      "is a small plaque.");
   add_item("jewels", "jewel", "Upon closer inspection you see that all " +
      "of the jewels are cheap glass imitations of the real thing.");
   add_item("gold", "The gold isn't especially impressive. It's just " +
      "painted onto the solid rock the statue is crafted from.");
   add_item("plaque", "The plaque reads, \"Fudge, where are you now?\"");
   add_item("bell", "The bronze bell looks extremely old. It is made of " +
      "bronze and has indecipherable writing and patterns on its " +
      "bottom edge, and a thick rope hangs from the clapper. It might " +
      "be possible to ring it.");

   add_room_command("ring", "do_ring");
}

int do_ring(string arg) {
   if (arg == "bell") {
      this_player()->simple_action ("$N $vring the bell.  A deep, " +
         "sonorous toll echoes across the square.");
   } else
      write("Ring what?");
}
