inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Road");
   set_long("You are on a road going out of the village. Eastroad runs " +
      "north from here, along the eastern perimeter of the city, and to " +
      "the south are some fields planted with all the crops that the " +
      "city needs. The main road runs towards the shore to the east, " +
      "and into the city to the west.");

   add_exit("north","/domains/2.4.5/rooms/eastroad1.c");
   add_exit("south","/domains/2.4.5/rooms/crop.c");
   add_exit("east","/domains/2.4.5/rooms/jetty.c");
   add_exit("west","/domains/2.4.5/rooms/vill_road2.c");
}
