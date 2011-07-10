inherit "/std/room";

void setup( void ) {
  set_brief( "%^YELLOW%^Bug room%^RESET%^" );
  set_long( "The room contains a huge and fluffy chair, since wizards " +
    "spend a lot of time in this room reading the bugreports from the " +
    "players. " );
  add_item( "chair", "The chair is really worn down, and has a big 'dent' " +
    "in it which looks like a perfect match for someone's butt." );
  set_objects( ([ "/obj/bug_board" : 1,
  ]) );
}
