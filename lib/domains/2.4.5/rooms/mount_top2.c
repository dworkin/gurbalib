inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Plateau");
   set_long("You are on a large, open plateau on top of the mountain.  " +
      "The view is fantastic in all directions and the clouds that " +
      "rush past above, feel so close you could almost touch them.  " +
      "The air here is fresh and clean.");

   add_exit("west","/domains/2.4.5/rooms/mount_top.c");
}
