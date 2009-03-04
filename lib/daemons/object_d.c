static object *objs;

void create( void ) {
  objs = ({ });
}

void register_object( object ob ) {
  if( !objs )
    objs = ({ });

  objs -= ({ ob });
  objs += ({ ob });
}

void unregister_object( object ob ) {
  if( !objs )
    objs = ({ });

  objs -= ({ ob });
}

int query_number_objects( void ) {
  return( sizeof( objs ) );
}

object *query_objects( void ) {
  return( objs );
}