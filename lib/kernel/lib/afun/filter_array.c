mixed *filter_array(mixed * arr, mixed fun, varargs mixed arg... ) {
   mixed *extra;
   object obj;
   mixed *res;
   int i, sz;

   argcheck(arrayp(arr), 1, "array");
#ifdef CLOSURES_EXTENSION
   argcheck(stringp(fun) || functionp(fun), 2, "function or string");
#else
   argcheck(stringp(fun), 2, "string");
#endif

   if (sizeof(arg)) {
#ifdef CLOSURES_EXTENSION
      if (functionp(fun)) {
         extra = arg;
      } else
#endif
      if (objectp(arg[0])) {
         obj = arg[0];
      } else if (stringp(arg[0])) {
         obj = find_object(arg[0]);
      }
      if (!extra) {
         argcheck(objectp(obj), 3, "object or string");
         extra = arg[1..];
      }
   } else {
      obj = this_object();
      extra = ({ });
   }

   res = ( { } );

   sz = sizeof(arr);
   for (i = 0; i < sz; i++) {
      mixed r;
#ifdef CLOSURES_EXTENSION
      if (functionp(fun)) {
         r = (*fun)(arr[i], extra...);
      } else {
         r = call_other(obj, fun, arr[i], extra...);
      }
# else 
      r = call_other(obj, fun, arr[i], extra...);
#endif

      if (r) {
         res += ( { arr[i] } );
      }
   }

   return res;
}
