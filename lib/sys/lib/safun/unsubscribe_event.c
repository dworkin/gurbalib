void unsubscribe_event(string name) {
   argcheck(name, 1, "string");

   if (events && events[name]) {
      events[name][previous_object()] = nil;
   }
}
