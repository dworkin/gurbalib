inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Mountain pass");
   set_long("You are in a pass going into the mountain with a steep " +
     "slope upwards to the north.  However, the path is barred.  There " +
     "is a tunnel entrance to the north.  It might be possible to clib " +
     "up, though.");

   add_exit("north","/domains/2.4.5/rooms/vill_shore.c");
   add_hidden_exit("up","/domains/2.4.5/rooms/ravine.c");
}

// XXX Need to add a climb command that will call move to ravine...
