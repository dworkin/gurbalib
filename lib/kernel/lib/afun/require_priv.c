/*
 * Test if all objects and programs have the requested privilege
 * (or a superior one that can become the requested privilege)
 */
nomask static int require_priv(string priv) {
   if (!secure_d) {
      secure_d = find_object(SECURE_D);
   }

   if (!secure_d) {
      return 0;
   }
  
   if (!priv) {
      return 1;
   }
   return secure_d->validate_stack(priv);
}
