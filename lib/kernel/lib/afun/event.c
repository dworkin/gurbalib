void event( string name, varargs mixed args... ) {
  object *obs;
  int i;

  obs = events[name];
  for( i = 0; i < sizeof( obs ); i++ ) {
    if( obs[i] )
      call_other( obs[i], "event_" + name, args );
  }
}

