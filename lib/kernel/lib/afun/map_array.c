static mixed *map_array(mixed * arr, string fun, mixed ob, varargs mixed extra) {
   mixed *result;
   int i, sz;

   argcheck(arrayp(arr), 1, "array");
   argcheck(stringp(fun), 2, "string");
   argcheck((stringp(ob) || objectp(ob)), 3, "object or string");

   sz = sizeof(arr);
   result = allocate(sz);

   for (i = 0; i < sz; i++) {
      result[i] = call_other(ob, fun, arr[i]);
   }
   return result;
}
