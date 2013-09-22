int strstr(string search, string what) {
   int i, lw, ls, sz;

   argcheck(search, 1, "string");
   argcheck(what, 2, "string");

   ls = strlen(search);
   lw = strlen(what) - 1;
   sz = ls - lw;
   for (i = 0; i < sz; i++) {
      if (search[i..(i + lw)] == what) {
	 return i;
      }
   }
   return -1;
}
