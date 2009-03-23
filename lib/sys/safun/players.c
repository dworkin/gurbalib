object * players() {
  int i,sz;
  object *p;
  object *u;
  object player;

  u = users();
  p = ({ });

  for( i = 0, sz = sizeof( u ); i < sz; i++ ) {
    if( player = u[i]->query_player() ) {
      p += ({ player });
    }
  }
  return p;
}

