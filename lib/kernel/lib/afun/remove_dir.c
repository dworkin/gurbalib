int remove_dir(string dir) {
   if (!valid(dir, MODE_WRITE)) {
#ifdef ENABLE_STACK_SECURITY
      console_msg("Access to " + dir + " denied\n");
      return 0;
#else
      console_msg("Access to " + dir +
         " would have been denied, ignoring...\n");
#endif
   }

   return::remove_dir(dir);
}
