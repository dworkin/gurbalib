static string owner_file(string file) {
   if (secure_d) {
      return secure_d->owner_file(file);
   } else {
      return DRIVER->owner_file(file);
   }
}
