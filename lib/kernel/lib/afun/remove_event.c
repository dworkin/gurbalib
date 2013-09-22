void remove_event(string name) {
   argcheck(name, 1, "string");

   if (events) {
      events[name] = nil;
   }
}
