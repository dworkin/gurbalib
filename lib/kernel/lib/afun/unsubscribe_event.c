void unsubscribe_event( string name ) {
  events[name] -= ({ previous_object() });
}

