inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("%^MAGENTA%^The general store.%^RESET%^");
   set_long("Still under contstruction.");

   set_exits(([
      "east" : "/domains/boothill/rooms/infront_store.c", 
   ]));

}
