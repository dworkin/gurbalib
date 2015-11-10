#include <privileges.h>

#define AUTH_DATA_DIR "/sys/daemons/data/users"

string name;
string password;
int    priv;

static void secure(void) {
   /* 
    * Checking previous_program() is cheap, require_priv isn't.
    * Since we are normally only called from USER_D, this will
    * save on a lot of overhead. USER_D could lie about any data
    * in here to the rest of the lib anyway, so we just trust it.
    */
   if (previous_program(1) != USER_D && !require_priv("system")) {
      error("Access denied.");
   }
}

static void save_me(void) {
   if (!query_guest(name)) {
      /* unguarded so a user can save its own data */
      unguarded("save_object", AUTH_DATA_DIR + "/" + name + ".o");
   }
}

int load(string str) {
   string file;

   secure();

   file = AUTH_DATA_DIR + "/" + str + ".o";

   priv = 0;
   name = nil;
   password = nil;

   /* we are either called from USER_D, or did a require_priv("system")
      already */
   return unguarded("restore_object", file);
}

int test(string user, string str) {
   secure();

   if (hash_string("SHA1", str, user) == password) {
      return 1;
   }
   return (hash_string("crypt", str, "gurba") == password);
}

void set_name(string str) {
   secure();

   name = str;
}

void set_pass(string user, string str) {
   secure();

   password = hash_string("SHA1", str, user);
   save_me();
}

void set_type(int i) {
   secure();

   priv = i;
   save_me();
}

int query_type(void) {
   return priv;
}
