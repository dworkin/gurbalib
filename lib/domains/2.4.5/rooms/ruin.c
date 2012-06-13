inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Ruin");
   set_long("A very old looking ruin.  There is no roof, and no door.");

   add_exit("north","/domains/2.4.5/rooms/plain4.c");
   add_exit("south","/domains/2.4.5/rooms/plain8.c");
   add_exit("east","/domains/2.4.5/rooms/plain9.c");
   add_exit("west","/domains/2.4.5/rooms/plain3.c");
}
