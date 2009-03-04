inherit ob   OBJECT;
inherit wear M_WEARABLE;
inherit      M_GETTABLE;
inherit      ARMOR_CLASS;

void setup( void );

void create( void ) {
  ob::create();
  wear::create();
  add_ids( "armor", "armour" );
}


