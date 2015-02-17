nomask string base_name(varargs object obj) {
   string obname, str;
   int clone;

   if (!obj) {
      obj = this_object();
   }

   obname = object_name(obj);

   if (sscanf(obname, "%s#%d", str, clone) == 2) {
      return str;
   }

   return obname;
}
