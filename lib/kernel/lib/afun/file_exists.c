int file_exists(string str) {
   mixed *val;
   int *sizes;
   string dir;

   argcheck(str, 1, "string");

   if (!KERNEL() && !SYSTEM() ) {
      dir = normalize_path(str, "/");
      if (!valid(dir, MODE_READ)) {
#ifdef ENABLE_STACK_SECURITY
         return 0;
#else
         console_msg("Access to " + str +
            " would have been denied, ignoring...\n");
#endif
      }
   }
   val = get_dir(str);
   sizes = val[1];

   if (!sizes || sizeof(sizes) == 0) {
      return 0;
   }

   if (sizes[0] == -2) {
      return -1;
   }

   return 1;
}
