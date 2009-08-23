
inherit "/std/room";

private string myname() {
  return capitalize( owner_file( file_name() ) );
}

void setup( void ) {
  set_brief( "%^RED%^" + myname() + "'s workroom%^RESET%^" );
  set_long( "The room is splashed with gore. Piles of limbs in one corner"
	    + " and piles of guts in another corner. In the middle of the room"
	    + " is a desk. On the desk are some grotesque looking tools." );
  set_exits( ([ "out"  : "/domains/gurba/town_square",
	        "east" : "/domains/gurba/bug_room",
	      ]) );

  add_item( "desk", "The desk is a huge and made of mahogny. It's the central piece of furniture of the room, and it is clear that " + myname() + " spends a lot of time behind it." );

  add_item( "tools", "They are used by grand master " + myname() + " to dissect monsters while trying to figure out how strong they are and where to place them." );

  add_item( "gore", "Youck!" );

  add_item( "limbs", "The ankle bone is connected to the leg bone. It's disgusting." );

  set_objects ( ([
		  "/domains/gurba/objects/chest" : 1,
		  "/domains/gurba/monsters/rat" : 1,
		  "/domains/gurba/objects/weapons/short_sword" : 1,
		  "/domains/gurba/objects/armor/buckler" : 1,
  ]));

}
