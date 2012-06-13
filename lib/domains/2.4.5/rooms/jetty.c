inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Road");
   set_long("You are on a road going out of the villate.  To the east " +
      "the road widens out as it leads down to the shore.  " +
      "To the west lies the city.");

   add_exit("east","/domains/2.4.5/rooms/vill_shore2.c");
   add_exit("west","/domains/2.4.5/rooms/vill_shore.c");
}
