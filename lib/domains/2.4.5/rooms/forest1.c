inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("In a forest");
   set_long("You are in a big forest.");

   add_exit("north","/domains/required/rooms/start.c");
   add_exit("east","/domains/2.4.5/rooms/wild1.c");
   add_exit("west","/domains/2.4.5/rooms/clearing.c");

   set_objects (([
      "/domains/2.4.5/obj/jacket.c": 1,
   ]));
}
