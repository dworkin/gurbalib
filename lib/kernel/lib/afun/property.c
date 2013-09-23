nomask mixed property(string name) {
   if (properties && properties[name] && require_priv(properties[name][0])) {
      return properties[name][2];
   }
   return nil;
}
