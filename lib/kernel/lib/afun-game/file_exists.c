string get_path_to_file(string file) {
   int i, done;

   done = 0;
   i = strlen(file);
   while (i > 0 && !done) {
      i--;
      if (file[i] == '/') {
	 done = 1;
      }
   }
   if (i <= 1)
      return "/";
   else {
      i--;
      return file[0..i];
   }
}

nomask static int file_exists(string file) {
   string dir;

   dir = get_path_to_file(file);

   if (!valid(dir, MODE_READ)) {
#ifdef ENABLE_STACK_SECURITY
      return 0;
#else
      console_msg("Access to " + file +
	 " would have been denied, ignoring...\n");
#endif
   }
   return::file_exists(file);
}
