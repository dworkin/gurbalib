#define BUFSZ 16384

static void copy(string src, string dst) {
   string buf;
   int pos, len;
   
   argcheck(src != nil, 1, "non empty string");
   argcheck(dst != nil, 2, "non empty string");

   if (!KERNEL() && !SYSTEM() ) {
      if (!valid(src, MODE_READ)) {
         error("Access to " + src + " denied");
      }

      if (!valid(dst, MODE_WRITE)) {
         error("Access to " + dst + " denied");
      }
   }
   
   pos = 0;
   len = 0;

   if (file_exists(dst) < 0) {
      string *parts;
      parts = explode(src, "/");
      dst += "/" + parts[sizeof(parts) - 1];
   }

   if (file_exists(dst) > 0) {
      remove_file(dst);
   } else if (file_exists(dst) < 0) {
      error("Cannot create destination file");
   }

   do {
      buf = read_file(src, pos, BUFSZ);
      write_file(dst, buf, pos);
      len = strlen(buf);
      pos += len;
   } while (len == BUFSZ);
}
