int armor_class;

int is_armor( void ) {
  return( 1 );
}

void set_ac( int ac ) {
  armor_class = ac;
}

int query_ac( void ) {
  return( armor_class );
}
