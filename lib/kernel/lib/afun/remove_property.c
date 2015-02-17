nomask int remove_property(string name) {
   if (properties && properties[name] && require_priv(properties[name][1])) {
      properties[name] = nil;
      return 1;
   }

   return 0;
}
