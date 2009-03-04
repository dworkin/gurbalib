inherit ARMOR;

void setup( void ) {
  set_id( "jacket" );
  set_adj( "leather", "black" );
  set_long( "This is the kind of leather jacket all %^RED%^bad%^RESET%^ dudes wear." );
  set_in_room_desc( "A hip leather jacket." );
  set_gettable( 1 );
  set_slot( "body" );
  set_wear_message( "$N $vput on $o. Man, $N $vare cool!" );
  set_remove_message( "$N $vtake off $o, and suddenly $vlook extremely dull." );
}
