inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Village shore");
   set_long("The village shore.  A jetty leads out to the east.  To the " +
      "north some stairs lead down to the north beach.  " +
      "A road starts to the west");

   add_exit("east","/domains/2.4.5/rooms/jetty2.c");
   add_exit("west","/domains/2.4.5/rooms/jetty.c");
}
