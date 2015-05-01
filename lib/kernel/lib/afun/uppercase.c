string uppercase(string str) {
   int i, sz;

   argcheck(str, 1, "string");

   sz = strlen(str);
   for (i = 0; i < sz; i++) {
      if (str[i] >= 'a' && str[i] <= 'z') {
         str[i] -= 'a' - 'A';
      }
   }
   return str;
}
