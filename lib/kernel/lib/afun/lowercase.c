string lowercase(string str) {
   int i, sz;

   argcheck(str, 1, "string");

   sz = strlen(str);
   for (i = 0; i < sz; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z') {
         str[i] += 'a' - 'A';
      }
   }
   return str;
}
