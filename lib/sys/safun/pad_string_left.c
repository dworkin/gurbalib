string pad_string_left(int len) {
   int i;
   string str;

   for (i = 0, str = ""; i < len; i++) {
      str += " ";
   }

   return str;
}
