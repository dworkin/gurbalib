inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("%^MAGENTA%^A prarie.%^RESET%^");
   set_long("The prarie is lush and green.  It extends to the west.  " +
      "To the east you see a road.");

   set_exits(([
      "east" : "/domains/boothill/rooms/entrance.c", 
      "west" : "/domains/required/rooms/start.c", 
   ]));
}
