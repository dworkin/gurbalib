inherit ROOM;

void setup( void ) {
  set_brief( "Gurba Bank" );
  set_long( "This is the main bank branch of Gurba. There are two large counters with a clerk behind each. One sign above the counter says 'Withdraw', while the other reads 'Deposit'. The floor and columns supporting the roof are made of what appears to be marble.");
  set_exits( ([ 
              
	       "south" : "/domains/gurba/rooms/border_south9",
 ]) );
  
  add_item( "counter", "counters", "Each of the counters are made out of solid oak." );
  add_item( "floor", "columns", "column", "The are nicely cut and tiled out of what seems to be marble, though upon closer inspection it seems to be fake." );
  set_objects( ([ 
  ]) );
  
}

