void remove_event( string name ) {
  argcheck( name, 1, "string" );
  events[name] = nil;
}

