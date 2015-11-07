void event(string name, varargs mixed args ...) {
   object *obs;
   int i, sz;

   argcheck(name, 1, "string");

   if (!events[name]) {
      return;
   }

   obs = map_indices(events[name]);

   sz = sizeof(obs);
   for (i = 0; i < sz; i++) {
      if (obs[i]) {
         call_other(obs[i], "event_" + name, args);
      }
   }
}
