inherit OBJECT;
// inherit M_EATABLE;
// XXX Needs work....

void setup( void ) {
  set_id( "potion" );
  set_short("potion of healing");
  set_long( "A red potion in a fancy bottle.\n");
  set_edable(1);
}

int do_eat( void ) {
  int x;

  x = random(5) + 1;
  write("You drink the potion.  You feel a warmth in your chest.\n");
  this_player()->increase_hp(x);
  this_object()->destruct();
}
