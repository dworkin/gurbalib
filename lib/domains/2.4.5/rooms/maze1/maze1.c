inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("In a maze");
   set_long("There are four obvious exits: north, south, east, west");

}

// XXX Need to figure out fake exits...
int do_movement() {
   exit_num = random(4);
   if (exit_num == 2) {
      room = "/domains/2.4.5/rooms/maze1/maze2.c";
   } else {
      room = "/domains/2.4.5/rooms/well.c";
   }

}
