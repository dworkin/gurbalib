#include <status.h>


#define RT status()[ST_TICKS]
#define MT (MAX_TICKS/2)

static mapping global_events;
int eventid;

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

void dispatch_event( string name, object *obs, int * counters, mixed *args ) {
  int i, max_i, guard_handle;

  eventid++;

  i = counters[0];
  max_i = counters[1];

#ifdef DEBUG_EVENT_D
  if(i == max_i)
    console_msg("dispatch_event( \""+name+"\" ) : "+(i+1)+" out of "+(max_i+1)+"\n");
#endif

  /* First see if there are any more objects after this one */
  if ( i < max_i ) {
    /* Go ahead and dispatch for the next one to make sure all get the event
       in case of errors */
    guard_handle = call_out("dispatch_event", 0, name, obs, counters, args );
  } else {
    guard_handle = 0;
  }

  while( RT > MT && i <= max_i ) {
    counters[0] = i + 1;

    if( obs[i] ) {
      if ( sizeof(args) > 0 )
        call_other( obs[i], "event_" + name, args );
      else
        call_other( obs[i], "event_" + name );
    }
    i++;
  }
#ifdef DEBUG_EVENT_D
  console_msg("dispatch_event: "+name+": next: "+(counters[0]+1)+" out of "+(counters[1]+1)+"\n");
#endif
  if(guard_handle && (counters[0] > counters[1])) {
    remove_call_out(guard_handle);
  }
}


void event( string name, varargs mixed args... ) {
  object *obs;
  int i;

  if(!global_events[name]) return;

  obs = map_indices(global_events[name]);

  if( !obs || sizeof(obs) == 0 )
    return;

#ifdef DEBUG_EVENT_D
  console_msg("Starting dispatch chain for event_"+name+" ("+eventid+"), "+sizeof(obs) +" subscribers.\n"); 
#endif
  dispatch_event( name, obs, ({ 0, sizeof(obs) - 1 }), args );  
}
