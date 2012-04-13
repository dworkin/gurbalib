inherit ROOM;

void setup(void) {
   add_area("boothill");

   set_brief("%^MAGENTA%^Your friendly neighborhood jail.%^RESET%^");
   set_long("There isn't a whole heck of a lot here.  Infact there is " +
      "a single cell to the east and thats pretty much it.");

   set_exits(([
      "west" : "/domains/boothill/rooms/infront_jail.c", 
      "east" : "/domains/boothill/rooms/cell.c", 
   ]));

}
