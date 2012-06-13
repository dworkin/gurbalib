inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Top of mountain");
   set_long("You are on top of a mountain.  THere is a small plateau to the " +
      "east.");

   add_exit("east","/domains/2.4.5/rooms/mount_top2.c");
   add_exit("down","/domains/2.4.5/rooms/ravine.c");
}
