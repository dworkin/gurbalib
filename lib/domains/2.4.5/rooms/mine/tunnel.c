inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Mine entrance");
   set_long("This is the entrance to the mines.  There is a sign on a pole.");

   add_exit("north","/domains/2.4.5/rooms/tunnel2.c");
   add_exit("south","/domains/2.4.5/rooms/mount_pass.c");

   add_item("sign","WARNING!!\n\nThe mines are closed due to risk of " +
      "falling rock.");
}
