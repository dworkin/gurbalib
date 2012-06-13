inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The local pub");
   set_long("You can order drinks here.");

   add_exit("west","/domains/2.4.5/rooms/yard.c");
}

// XXX Add menu, and only allow exit if you don't have drinks anymore...

