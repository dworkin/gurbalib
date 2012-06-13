inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("A path");
   set_long("You are on a path going east-west.  There are some VERY big " +
      "footsteps here.");

   add_exit("east","/domains/2.4.5/rooms/big_tree.c");
   add_exit("west","/domains/2.4.5/rooms/giant_lair.c");
}
