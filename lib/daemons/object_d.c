static mapping objs;

void create( void ) {
  objs = ([ ]);
}

void register_object( object ob ) {
  if( !objs )
    objs = ([ ]);

  objs[ob] = 1;
}

void unregister_object( object ob ) {
  if( !objs )
    objs = ([ ]);

  objs[ob] = nil;
}

int query_number_objects( void ) {
  return( map_sizeof( objs ) );
}

object *query_objects( void ) {
  return( map_indices(objs) );
}
