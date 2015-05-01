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
   if (i <= 1) {
      return "/";
   } else {
      i--;
      return file[0..i];
   }
}
