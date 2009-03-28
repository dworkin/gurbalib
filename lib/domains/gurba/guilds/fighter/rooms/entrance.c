inherit ROOM;

void setup( void ) {
  set_brief( "Fighters Guild Atrium" );
  set_long( "You are standing in the magnificent atrium of the Gurba Fighter's Guild. It is a massive room covered by a tall dome; from the center of the dome a massive bronze chandelier is hung. There are weapons and armor hung on the walls. The ancient stonework is etched with the names of heroic and legendary fighters of the past. Fighters are sparring here and there, the clangs of their weapons echoing throughout the hall. To the south lies Gelmir Road, and to the north is the entrance to the guild itself." );
  set_exits( ([ 
	       "south" : "/domains/gurba/rooms/gelmir3",
	       "north" : "/domains/gurba/guilds/fighter/rooms/main",
  ]) );

  set_objects( ([
		 "/domains/gurba/guilds/fighter/monsters/master" : 1 
		 ])
	       );

  add_item( "wall", "walls", "stonework", "weapons", "armor", "The walls are made of businesslike solid stone, and are hung with many old rusty weapons and armor. Names such as 'Hrundor the Uncouth' are scrawled next to some of them." );
  add_item( "chandelier", "This humongous chandelier is held up by a giant metal chain of ridiculous weight and strength. The chain runs down to a large spool on one side of the room, allowing the chandelier to be lowered and the large candles replaced once a day." );
  add_item( "fighters", "Some intrepid young fighters are practicing their art in here. It's no small wonder the stone floors are stained with blood." );
}

void do_listen( void ) {
  write( "To the north you hear metal clanging against metal, and the odd cry in agony. Once in a while you hear muffled laughter as well." );
}
