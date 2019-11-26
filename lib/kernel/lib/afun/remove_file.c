int remove_file(string file) {
   if (!valid(file, MODE_WRITE)) {
#ifdef ENABLE_STACK_SECURITY
      console_msg("Access to " + file + " denied\n");
      return 0;
#else
      console_msg("Access to " + file +
         " would have been denied, ignoring...\n");
#endif
   }

   return::remove_file(file);
}
