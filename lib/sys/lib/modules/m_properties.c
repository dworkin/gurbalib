mapping properties;

nomask int set_property(string name, mixed value, varargs string rpriv, 
   string wpriv) {

   if (!properties) {
      properties = ([ ]);
   }

   if (!properties[name] || require_priv(properties[name][1])) {
      if (!rpriv) {
         if (properties[name]) {
            rpriv = properties[name][0];
         } else {
            rpriv = "*";
         }
      }

      if (!wpriv) {
         if (properties[name]) {
            wpriv = properties[name][1];
         } else {
            wpriv = rpriv;
         }
      }

      properties[name] = ({ rpriv, wpriv, value });
      return 1;
   }

   return 0;
}

nomask void set_property_file(string path) {
   string *lines, *parts;
   string key, val;
   int i, dim, property_was_set;

   property_was_set = 0;
   if (file_exists(path) == 1) { /* valid read has to be assumed. */
      lines = explode(read_file(path), "\n");
      for (i = 0, dim = sizeof(lines); i < dim; i++) {
         if (lines[i][0] == '#') {
            continue;
         }
         parts = explode(lines[i], "=");
         if (sizeof(parts) == 2) {
            key = parts[0];
            val = parts[1];
         } else if (sizeof(parts) > 2) {
            key = parts[0];
            val = implode(parts[1..], "=");
         } else {
            key = nil;
         }
         if (!nilp(key)) {
            property_was_set = set_property(key, val, "*");
         }
      }
   }
}

nomask int remove_property(string name) {
   if (properties && properties[name] && require_priv(properties[name][1])) {
      properties[name] = nil;
      return 1;
   }

   return 0;
}

nomask mixed property(string name) {
   if (properties && properties[name] && require_priv(properties[name][0])) {
      return properties[name][2];
   }
   return nil;
}
