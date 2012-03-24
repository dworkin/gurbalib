static void copy(string src, string dst) {
   argcheck(src != nil, 1, "non empty string");
   argcheck(dst != nil, 2, "non empty string");

   if (!valid(src, MODE_READ)) {
      error("Access to " + src + " denied");
   }

   if (!valid(dst, MODE_WRITE)) {
      error("Access to " + dst + " denied");
   }

   ::copy(src, dst);
}
