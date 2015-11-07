int member_array(mixed item, mixed * arr) {
   int i, sz;

   argcheck(arr, 2, "array");

   sz = sizeof(arr);
   for (i = 0; i < sz; i++) {
      if (arr[i] == item) {
         return i;
      }
   }
   return -1;
}
