void event( string name, varargs mixed args... ) {
  object *obs;
  int i;

  /* Remove objects that have vanished */
  events[name] -= ({ nil });
  obs = events[name];

  /* Use the event daemon to send the event */
  EVENT_D->dispatch_event( name, obs, 0, sizeof(obs) - 1, args );
}

