static mapping global_events;

void create( void ) {
  global_events = ([ ]);
}

void add_event( string name ) {
  if( !global_events )
    global_events = ([ ]);
  global_events[name] = ({ });
}

void remove_event( string name ) {
  global_events[name] = nil;
}

void subscribe_event( string name ) {
  global_events[name] -= ({ previous_object() });
  global_events[name] += ({ previous_object() });
}

void unsubscribe_event( string name ) {
  global_events[name] -= ({ previous_object() });
}

void event( string name, varargs mixed args... ) {
  object *obs;
  int i;

  obs = global_events[name];
  if( !obs )
    return;

  for( i = 0; i < sizeof( obs ); i++ ) {
    if(sizeof(args) > 0)
      call_other( obs[i], "event_" + name, args );
    else
      call_other( obs[i], "event_" + name);
  }
}