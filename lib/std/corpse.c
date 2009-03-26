inherit OBJECT;

static string orig_name;

void create( void ) {
  ::create();
  call_out( "decompose", 30 );
  set_id( "corpse" );
  set_in_room_desc( "A foul smelling corpse." );
  set_long( "It looks just as awful as it smells." );
}

void set_name( string name ) {
  orig_name = name;
  set_in_room_desc( "The corpse of " + name );
}

void decompose( void ) {
  call_out( "destruct", 30 );
  if(!orig_name) orig_name = "noone";

  set_in_room_desc( "The somewhat decayed corpse of " + orig_name );
}
  
