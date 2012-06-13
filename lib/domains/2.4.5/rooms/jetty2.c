inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Jetty");
   set_long("You are at a jetty.  The waves roll in from the east.  " +
      "A small path leads back to the west.");

   add_exit("east","/domains/2.4.5/rooms/sea.c");
   add_exit("west","/domains/2.4.5/rooms/vill_shore2.c");

  set_objects (([
   "/domains/2.4.5/obj/bag.c": 1,
  ]));
}
