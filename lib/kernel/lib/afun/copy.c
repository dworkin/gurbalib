#define BUFSZ 16384

static void copy(string src, string dst) {
   string buf;
   int pos, len;

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
