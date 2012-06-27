inherit ROOM;
#define DIR "/domains/boothill"

void setup(void) {
   add_area("boothill");

   set_brief("Your friendly neighborhood jail");
   set_long("There isn't a whole heck of a lot here.  Infact there is " +
      "a single cell to the east and thats pretty much it.");

   set_exits(([
      "west" : DIR + "/rooms/infront_jail.c", 
      "east" : DIR + "/rooms/cell.c", 
   ]));

}
