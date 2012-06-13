inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Village track");
   set_long("A track going into the village.  The track opens up to a road " +
      "to the east and ends with a green lawn to the west.");

   add_exit("east","/domains/2.4.5/rooms/hump.c");
   add_exit("west","/domains/2.4.5/rooms/forest1.c");
}
