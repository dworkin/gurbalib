/*
 * Run object with custom privileges.
 *
 */

#include <privileges.h>

private string cpriv;

nomask static void run_as(string priv) {
   if(ROOT()) {
      string *parts;
      int i, sz, pt;

      if (owner_file(object_name(this_object())) != "system") {
         error("Attempt to set custom privileges in non system object");
      }

      parts = explode(priv,":");
      for(i=0, sz=sizeof(parts); i<sz; i++) {
         pt = SECURE_D->query_priv_type(parts[i]);
         if(pt == PT_UNKNOWN || parts[i] == "-" || parts[i] == "*" || parts[i] == "?") {
            error("Invalid privilege " + priv);
         }
      }
      cpriv = priv;
      SECURE_D->invalidate_pcache();
   } else {
      error("Illegal call to run_as");
   }
}

nomask string _Q_cpriv() {
   if(ROOT()) {
      if(cpriv) {
         return cpriv;
      } else {
         return owner_file(object_name(this_object()));
      }
   } else {
      error("Illegal call to _Q_cpriv");
   }
}
