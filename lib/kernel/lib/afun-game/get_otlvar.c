/*
 * Get the value for a tls 'per object' global variable.
 *
 * By Aidil@Way of the Force
 *
 * This code is in the public domain.
 */

static mixed get_otlvar(string name) {
   mapping vars;

   argcheck(stringp(name), 1, "string");

   vars = DRIVER->get_tlvar(TLS_OVARS);
   if (vars && vars[this_object()]) {
      return vars[this_object()][name];
   }
}
