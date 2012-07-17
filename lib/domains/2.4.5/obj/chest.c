inherit CONTAINER;

void setup(void) {
   set_id("chest");
   set_in_room_desc("a chest");
   set_long("A chest that seems to be of a high value.");
   set_weight(8);
   set_gettable(1);
   set_value(200);
}

// XXX add weight of items in it to its weight should be in container code.
