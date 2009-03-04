
inherit ROOM;

void setup( void ) {
  set_brief( "%^MAGENTA%^The void%^RESET%^" );
  set_long( "If you're in here unintentionally, something bugged out. Report what you did to the staff." );
  set_exits( ([ 
	       "out" : "/domains/gurba/town_square",
  ]) );
}
