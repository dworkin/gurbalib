inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("East road");
   set_long("East road runs north-south.");

   add_exit("north","/domains/2.4.5/rooms/eastroad5.c");
   add_exit("south","/domains/2.4.5/rooms/eastroad3.c");
}
