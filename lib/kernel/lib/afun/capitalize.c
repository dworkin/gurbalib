string capitalize(string str) {
   argcheck(str, 1, "string");

   if (!str) {
      return str;
   }

   if (str[0] >= 'a' && str[0] <= 'z') {
      str[0] -= 'a' - 'A';
   }

   return str;
}
