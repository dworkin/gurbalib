inherit ROOM;

void setup(void) {
   add_area("newbie");

   set_brief("%^MAGENTA%^Ye old saloon.%^RESET%^");
   set_long("A large wooden bar streaches across the back of the room.  " +
      "Other than that the room is currently pretty empty.  There are " +
      "a bunch of chairs pushed up against tables scattered about the room.");

   set_exits(([
      "west" : "/domains/boothill/rooms/infront_saloon.c",
   ]));

   add_object("/domains/boothill/obj/piano.c",1);
}
