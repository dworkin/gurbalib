int strstr(string search, string what) {
   int i, lw, ls;

   argcheck(search, 1, "string");
   argcheck(what, 2, "string");

   ls = strlen(search);
   lw = strlen(what) - 1;
   for (i = 0; i < (ls - lw); i++) {
      if (search[i..(i + lw)] == what)
	 return i;
   }
   return (-1);
}
