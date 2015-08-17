void add_event(string name) {
   if (!events) {
      events = ([]);
   }

   if (!events[name]) {
      events[name] = ([]);
   }
}
