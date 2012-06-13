inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Ravine");
   set_long("You are in a ravine between mountaions.  It seems to be " +
      "possible to go up from here.");

   add_exit("up","/domains/2.4.5/rooms/mount_top.c");
   add_exit("down","/domains/2.4.5/rooms/mount_pass.c");
}
