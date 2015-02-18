int absolute_path(string dir) {
   if (!dir || dir == "") {
      return 0;
   }

   if (dir[0] == '/' || dir[0] == '~') {
      return 1;
   }

   return 0;
}
