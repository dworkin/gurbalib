inherit OBJECT;
inherit M_GETTABLE;

void setup( void ) {
  set_id( "potion" );
  set_adj("small", "healing", "red");
  set_long( "A small fancy bottle, with a faintly glowing red liquid in it.  " +
     "A label on the bottle says ode de Healing.\n");

  // Why doesn't this work??? XXX
  set_brief( "A small red potion");

  set_edable( 1 );
  set_gettable( 1 );
}

int do_eat( void ) {
  int x;

  x = random(5) + 1;
  write("You drink the potion.  You feel a warmth in your chest.\n");
  this_player()->increase_hp(x);
  this_object()->destruct();
}
