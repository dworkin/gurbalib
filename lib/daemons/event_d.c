static mapping global_events;

void create( void ) {
  global_events = ([ ]);
}

void add_event( string name ) {
  if( !global_events ) {
    global_events = ([ ]);
  }

  if( !global_events[name] ) {
    global_events[name] = ([]);
  }
}

void remove_event( string name ) {
  global_events[name] = nil;
}

void subscribe_event( string name ) {
  global_events[name][previous_object()] = 1;
}

void unsubscribe_event( string name ) {
  global_events[name][previous_object()] = nil;
}

void dispatch_event( string name, object *obs, int i, int max_i, mixed *args ) {
  /* First see if there are any more objects after this one */
  if ( i < max_i ) {
    /* Go ahead and dispatch for the next one to make sure all get the event
       in case of errors */
    call_out("dispatch_event", 0, name, obs, i + 1, max_i, args );
  }
  if( obs[i] ) {
    if ( sizeof(args) > 0 )
      call_other( obs[i], "event_" + name, args );
    else
      call_other( obs[i], "event_" + name );
  }
}


void event( string name, varargs mixed args... ) {
  object *obs;
  int i;

  if(!global_events[name]) return;

  obs = map_indices(global_events[name]);

  if( !obs || sizeof(obs) == 0 )
    return;

  dispatch_event( name, obs, 0, sizeof(obs) - 1, args );  
}
