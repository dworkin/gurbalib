inherit ROOM;
#define DIR "/domains/boothill"

void setup(void) {
   add_area("boothill");

   set_brief("Ye old saloon");
   set_long("A large wooden bar streaches across the back of the room.  " +
      "Other than that the room is currently pretty empty.  There are " +
      "a bunch of chairs pushed up against tables scattered about the room.");

   set_exits(([
      "west" : DIR + "/rooms/infront_saloon.c",
   ]));

   set_objects(([
      DIR + "/obj/piano.c" : 1,
   ]));
}
