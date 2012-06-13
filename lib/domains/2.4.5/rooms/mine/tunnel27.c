inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Dead end");
   set_long("End of tunnel!");

   add_exit("south","/domains/2.4.5/rooms/tunnel26.c");
}
