inherit ROOM;
#define DIR "/domains/boothill"

void setup(void) {
   add_area("boothill");

   set_brief("A very small jail cell");
   set_long("There isn't a whole heck of a lot here.");

   set_exits(([
      "west" : DIR + "/rooms/jail.c", 
   ]));

}
