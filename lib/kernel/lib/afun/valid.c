/* Test if we have read or write access to 'file'. */
nomask static string valid(string file, int mode) {
   string priv;

   if (!secure_d) {
      secure_d = find_object(SECURE_D);
   }

   if (secure_d) {
      if (!mode) {
         priv = secure_d->query_read_priv(file);
      } else {
         priv = secure_d->query_write_priv(file);
      }
   } else {
      priv = "system";
   }

   if (require_priv(priv)) {
      return file;
   }

   return nil;
}
