inherit ob   OBJECT;
inherit wear M_WIELDABLE;
inherit      M_GETTABLE;
inherit	     M_VALUABLE;
inherit      ARMOR;

void setup( void );

void create( void ) {
  ob::create();
  wear::create();
  add_ids( "shield" );
}

