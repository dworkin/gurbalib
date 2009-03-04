inherit ROOM;

static int weather;

void set_weather( int flag ) {
  weather = flag;
}

int query_weather( void ) {
  return( weather );
}