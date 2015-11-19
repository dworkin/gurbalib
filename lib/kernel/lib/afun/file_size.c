/* get the size of a file in K, or 0 if the file doesn't exist */
int file_size(string file, varargs int dir) {
   mixed **info;
   string *files, name;
   int i, sz;

   argcheck(file, 1, "string");

   if (file == "/") {
      file = ".";
   }
   info = get_dir(file);
   files = explode(file, "/");
   name = files[sizeof(files) - 1];
   files = info[0];
   i = 0;
   sz = sizeof(files);

   if (sz <= 1) {
      if (sz == 0 || files[0] != name) {
         return 0;    /* file does not exist */
      }
   } else {
      /* name is a pattern: find in file list */
      while (name != files[i]) {
         if (++i == sz) {
            return 0;       /* file does not exist */
         }
      }
   }

   i = info[1][i];
   if (i > 0) {
      return i;
   } else if (i == 0) {
      return  1;
   } else if (i == -2 && dir) { 
      return dir_size(file);
   }
   return 0;
}
