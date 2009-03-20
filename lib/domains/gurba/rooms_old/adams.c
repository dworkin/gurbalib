
inherit ROOM;

void setup( void ) {
  set_brief( "%^RED%^Adams Boutique%^RESET%^" );
  set_long( "Welcome to Adams. This large wooden house is the base for Adams Business. The shop is filled with all kinds of trinkets, devices and art. Adam is standing behind the counter smiling at you, south lies Market boulevard." );
  set_exits( ([ 
               "south" : "/domains/gurba/rooms/market1",
	       ]) );
  
  add_item( "trinkets", "trinket", "All kinds of small coins, buttons, needles, pins and gizmos. Looking very shiny, tempting and expensive." );
  add_item( "devices", "device", "Numerous different inventiones are neatly displayed on the east wall, not that you would have any idea of what these things could be good for. " );
  add_item( "art", "Now this is culture! There are figurines on pedestals, paintings, both decent and otherwise. Statues and sculptures that could have been decoration for the King himself, in fact he even has a headpiece that used to belong to the King. Whith the biggest sideburns you ever saw. " );
 set_objects( ([ 
  ]) );
  
}

void do_listen( object player ) {
  write( "It is so quiet in here that you can hear the noises from outside." );
}

