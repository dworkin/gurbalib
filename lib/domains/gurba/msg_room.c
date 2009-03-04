
inherit "/std/room";

void setup( void ) {
  set_brief( "%^YELLOW%^Message room%^RESET%^" );
  set_long( "The room is furnished so that all attention is directed to the large board in the middle of the room. " );
  set_exits( ([ "west" : "/domains/gurba/town_square" ]) );
}
