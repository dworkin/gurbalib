inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("The adventures guild");
   set_long("You have to come here when you want to advance your level.  " +
      "You can also buy points for a new level.  There is an opening to the " +
      "south, and some shimmering blue light in the doorway.");
   add_exit("north","/domains/2.4.5/rooms/vill_road2.c");
   add_exit("south","/domains/required/rooms/bug_room.c");
}

// XXX more to add here...
