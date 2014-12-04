/*
 * Set the value for a tls 'super global'.
 *
 * By Aidil@Way of the Force
 *
 * This code is in the public domain.
 */
static void set_tlvar(string name, mixed value) {
   mapping vars;
   int save;

   argcheck(stringp(name), 1, "string");

   vars = DRIVER->get_tlvar(TLS_UVARS);

   if (!vars) {
      vars = ([]);
      save = 1;
   }

   vars[name] = value;

   /* * If we just initialized the mapping, save a * reference on the tls */
   if (save) {
      DRIVER->set_tlvar(TLS_UVARS, vars);
   }
}
