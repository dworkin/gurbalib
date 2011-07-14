inherit ROOM;

void setup( void ) {
   set_brief( "%^MAGENTA%^North end of field.%^RESET%^" );
   set_long( "You are in a large open field.  To the South you see a " +
   "road leading to a city.  There is an odd hole in a hill to the north.");
   set_exits( ([ 
      "south" : "/domains/required/rooms/start",
   ]) );
   set_objects( ([ 
      "/domains/required/objects/sign" : 1,
   ]) );
   add_item("hole", "A funny hole in the ground.  You might be able to " +
      "enter it.");
}

