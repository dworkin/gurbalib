void subscribe_event( string name ) {
  argcheck( name, 1, "string" );
  events[name] += ({ previous_object() });
}

