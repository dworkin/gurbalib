int clone_num(varargs object obj) {
   string str;
   int clone;

   if (!obj) {
      obj = this_object();
   }

   if (sscanf(object_name(obj), "%s#%d", str, clone) == 2) {
      return clone;
   }

   return 0;
}
