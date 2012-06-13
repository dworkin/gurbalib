inherit ROOM;

void setup(void) {
   add_area("2.4.5");

   set_brief("Elevator");
   set_long("You are in the elevator.  On the wall are three buttons, " +
      "numbered 1 to 3.");

   add_exit("north","/domains/2.4.5/rooms/vill_shore.c");
}

// XXX Need to do the door, button and stuff....
