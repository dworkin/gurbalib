inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("Boothill");
   set_long("If your not sure what boothill is, now you know, its a " +
      "cemetary just outside of town.  There are a bunch of cheap " +
      "graves here.  Including a freshly dug hole, just waiting for the " +
      "towns next victum.");

   set_exits(([
      "south" : "/domains/boothill/rooms/infront_jail.c", 
   ]));

}
