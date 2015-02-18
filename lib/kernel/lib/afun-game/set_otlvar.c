/*
 * Set the value for a tls 'per object' global variable.
 *
 * By Aidil@Way of the Force
 *
 * This code is in the public domain.
 */

static void set_otlvar(string name, mixed value) {
   mapping vars;
   int save;

   argcheck(stringp(name), 1, "string");

   vars = DRIVER->get_tlvar(TLS_OVARS);

   if (!vars) {
      vars = ([]);
      save = 1;
   }

   if (!vars[this_object()]) {
      vars[this_object()] = ([]);
   }

   vars[this_object()][name] = value;
   /*
    * If we initialized the vars mapping, we have to
    * store the new reference on the tls.
    */
   if (save) {
      DRIVER->set_tlvar(TLS_OVARS, vars);
   }
}
