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
