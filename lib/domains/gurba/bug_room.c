
inherit "/std/room";

void setup( void ) {
  set_brief( "%^YELLOW%^Bug room%^RESET%^" );
  set_long( "The room contains a huge and fluffy chair, since Fudge spends a lot of time in this room reading the bugreports from the players. " );
  set_exits( ([ "west" : "/wiz/fudge/workroom" ]) );
  add_item( "chair", "The chair is really worn down, and has a big 'dent' in it which looks like a perfect match of Fudges butt." );
  set_objects( ([ "/domains/gurba/objects/bug_board" : 1,
  ]) );
}
