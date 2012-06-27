inherit ROOM;
#define DIR "/domains/boothill"

void setup(void) {
   add_area("boothill");

   set_brief("Outside town");
   set_long("A small dirt road leads north to a small frontier town.");

   set_exits(([
      "north" : DIR + "/rooms/welcome.c", 
      "west" : DIR + "/rooms/outside_town.c",
   ]));
}
