inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Village green");
   set_long("You are at an open green place south of the village church.  " +
      "You can see a road further to the east.");

   add_exit("north","/domains/2.4.5/rooms/church.c");
   add_exit("east","/domains/2.4.5/rooms/vill_track.c");
   add_exit("west","/domains/2.4.5/rooms/hump.c");
}
