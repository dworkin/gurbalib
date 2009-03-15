
inherit ROOM;

void setup( void ) {
   set_area("Gurba");
   set_brief( "%^GREEN%^Gurba Town Square%^RESET%^" );
   set_long( "This is the natural meeting place in the town of Gurba. In the center of the square is a large statue of the city's founder. It's a breathtaking sight." );
   set_exits( ([ 
		  "west" : "/domains/gurba/rooms/market1", 
		  "east" : "/domains/gurba/rooms/gelmir1",
		  ]) );
   
   add_item( "statue", "A pretty large and well crafted statue of a small dwarf. It is decorated with fine jewels and gold, and at the base is a small plaque." );
   add_item( "jewels", "jewel", "Upon closer inspection you see that all of the jewels are cheap glass imitations of the real thing." );
   add_item( "gold", "The gold isn't especially impressive. It's just painted onto the solid rock the statue is crafted from." );
   add_item( "plaque", "The plaque says: Fudge, where are you now?" );
   
   set_objects( ([ "/domains/gurba/objects/main_board" : 1,
		   ]) );
   
}
