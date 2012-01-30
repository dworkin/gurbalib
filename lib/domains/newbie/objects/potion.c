inherit OBJECT;

void setup( void ) {
  set_id( "potion" );
  set_adj("small", "healing", "red");
  set_long( "A small fancy bottle, with a faintly glowing red liquid in it.  " +
     "A lable on the bottle says ode de Healing.\n");

  // WHy doesn't this work??? XXX
  set_brief( "A small red potion");

  set_edable(1);
}

int do_eat( void ) {
  int x;

  x = random(5) + 1;
  write("You drink the potion.  You feel a warmth in your chest.\n");
  this_player()->increase_hp(x);
  this_object()->destruct();
}
