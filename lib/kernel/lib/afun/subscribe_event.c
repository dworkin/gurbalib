void subscribe_event(string name) {
   argcheck(name, 1, "string");
   if (events[name])
      events[name][previous_object()] = 1;
}
