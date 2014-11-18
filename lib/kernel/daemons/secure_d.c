/* uncomment the line below to get a lot of debug output.. */
/* #define DEBUG_STACK_SECURITY */
/* uncomment the line below to get even more debug output.. */
/* #define DEBUG_STACK_SECURITY_DEEP */

#include <trace.h>
#include <tlsvar.h>
#include <privileges.h>

/*
 * During boot, the compiler daemon will not be available yet to
 * include std-kernel.h automatically. However, when this object
 * gets recompiled later, the compiler daemon will be there and
 * automatically include std-kernel.h
 */
#ifndef __KERNEL__
#include <std-kernel.h>
#endif

mapping privs, domains;

static void DB(string str) {
#ifdef DEBUG_STACK_SECURITY
   console_msg(str);
#endif
}

static void DBD(string str) {
#if defined(DEBUG_STACK_SECURITY) && defined(DEBUG_STACK_SECURITY_DEEP)
   console_msg(str);
#endif
}

static int restore_me(void) {
   return restore_object("/kernel/daemons/data/secure_d.o");
}

static void save_me(void) {
   save_object("/kernel/daemons/data/secure_d.o");
}

string *query_domains(void) {
   return DOMAIN_D->query_domains();
}

mapping query_domain_data(void) {
   if (ROOT()) {
      return domains;
   }
}

void domains_d_v2(void) {
   if (ROOT()) domains = nil;
}

void user_d_v2(void) {
   if (ROOT()) privs = nil;
}

/*
 * Since we are in kernel space, we don't have the query_wizard afun
 * available. The function below just serves as a redirect to an
 * object that does have it available and that should always exist
 * once the mud booted.
 *
 * This is required for /kernel/sys/driver.c which doesn't
 * know about user_d, and which shouldn't depend on anything outside
 * /kernel
 *
 * This is why we must check first if USER_D is loaded, this code 
 * can be called very early during boot if an error occurs.
 *
 */
int query_wizard(mixed p) {
   if (find_object(USER_D)) {
      return USER_D->query_wizard(p);
   }
   /* we don't know about wizards without USER_D, be safe */
   return 0;
}

string *query_wizards(void) {
   return filter_array(USER_D->list_all_users(), "query_wizard");
}

string *known_names(void) {
   string *result;
   result = SYS_BANNED_NAMES;
   result |= query_domains();
   result |= query_wizards();
   return result;
}

int query_priv_type(string p) {
   int r, priv;

   if (sizeof(SECURITY_NO_CHECK & ({ p }))) {
      r = PT_PREDEF | PF_NO_CHECK;
   } else if (sizeof(SECURITY_NO_ACCESS & ({ p }))) {
      r = PT_PREDEF | PF_NO_ACCESS;
   } else if (sizeof(SYS_BANNED_NAMES & ({ p }))) {
      r = PT_PREDEF;
   /* 
    * when USER_D is not loaded, we don't try to handle anything beyond 
    * predefined users. We want to leave loading USER_D to init, and
    * should ensure we don't rely on anything outside /kernel until
    * init is ready for that.
    */
   } else if (!find_object(USER_D)) {
      r = PT_UNKNOWN;
   } else if (DOMAIN_D->is_domain(p)) {
      if (file_exists(DOMAINS_DIR + "/" + p) != 0) {
         r = PT_DOMAIN;
      } else {
         r = PT_DOMAIN_BAD;
      }
   /* note, there is nothing special about the privilege with the 
      name of an admin */
   } else if (query_wizard(p)) {
      if (USER_D->player_exists(p)) {
         r = PT_WIZARD;
      } else {
         r = PT_WIZARD_BAD;
      }
   } else {
      if (USER_D->player_exists(p) || (p == "guest")) {
         r = PT_PLAYER;
      /* no player savefile, but user does exist */
      } else if (USER_D->user_exists(p)) {
         r = PT_PLAYER_BAD;
      } else {
         r = PT_UNKNOWN;
      }
   }
   return r;
}

static void create(void) {
   restore_me();
   DRIVER->register_secure_d();
}

void make_lockerdir(string domain, string pname) {
   string path;

   path = DOMAINS_DIR + "/" + domain + "/";

   if (file_exists(path) == -1) {
      path = path + "/data/";
      if (file_exists(path) == 0) {
         make_dir(path);
      }

      path = path + "/lockers/";
      if (file_exists(path) == 0) {
         make_dir(path);
      }

      path = path + "/" + pname + "/";
      if (file_exists(path) == 0) {
         make_dir(path);
      }
   } else {
      write("Cannot find domain:" + domain + "\n");
   }
}

void remove_player(string name) {
   string prev;

   prev = previous_object()->base_name();
   if (!require_priv("system")) {
      error("Access denied: " + prev + "\n");
   }

   name = lowercase(name);

   filter_array(map_indices(domains), "remove_domain_member", this_object(),
      name);
}

int query_priv(string name) {
   if (previous_program() != USER_D) {
      return USER_D->query_priv(name);
   } else {
      return privs[name];
   }
}

#define ROOT_OVERRIDE ({ })

/* Do the privileges provided in str contain a root privilege?  */
int root_priv(string str) {
   if (sscanf(str, "%*s:system:%*s") != 0 || 
      sscanf(str, "%*s:kernel:%*s") != 0) {
      return 1;
   }
}

/* Do the privileges provided in str include 'game' privileges?  */
int game_priv(string str) {
   if (sscanf(str, "%*s:game:%*s") != 0) {
      return 1;
   }
}

/*
 * Who 'owns' the file provided as argument? This is the filesystem owner
 * of that file, and is used for things like default privileges
 */
string owner_file(string file) {
   string *parts;
   string tmp;
   int i, sz;

   argcheck(file, 1, "string");

   if (sizeof(( { file } ) & ROOT_OVERRIDE)) {
      return "system";
   }

   parts = explode(file, "/");

   switch (parts[0]) {
      case "kernel":
         return "kernel";
         break;
      case "":
      case "sys":
      case "logs":
         return "system";
         break;
      case "daemons":
      case "std":
      case "data":
      case "cmds":
      case "pub":
         return "game";
         break;
      case "wiz":
         if (sizeof(parts) > 1 && query_wizard(parts[1])) {
            return parts[1];
         } else {
            return "game";
         }
         break;
      case "domains":
         if (sizeof(parts) > 1 && DOMAIN_D->is_domain(parts[1])) {
            return parts[1];
         } else {
            return "game";
         }
         break;
      case "tmp":
         if (sizeof(parts) > 1) {
            return "*";
         } else {
            return "game";
         }
   }
   if(sizeof(parts) == 1) {
      return "game";
   } else {
      return "nobody";
   }
}

/* Determine the privileges of an inheritable */
string determine_program_privs(string progname) {
   return ":" + owner_file(progname) + ":";
}

/* Determine the privileges for the object with the objectid 'objname' */
string determine_obj_privs(string objname) {
   string name, priv;
   object ob;

   ob = find_object(objname);

   if (ob && ob <- "/sys/lib/runas") {
      priv = ob->_Q_cpriv();
   } else {
      priv = owner_file(objname);
   }

   return ":" + priv + ":";
}

/* check if the privileges in spriv are enough to satisfy rpriv */
static int validate_privilege(string spriv, string rpriv) {
   if (root_priv(spriv) ||
      (game_priv(spriv) && DOMAIN_D->is_domain(rpriv)) ||
      (sscanf(spriv, "%*s:" + rpriv + ":%*s") != 0)) {
      return 1;
   }
}

/*
 * The stack validator, this is what it is all about..
 *
 * Gets a call_stack, and loops through it to determine the 
 * privileges of all objects and inheritables that brought us
 * to where we are now. It then matches those privileges against
 * the required privilege provided in the priv argument.
 * Optionally, unguarded can be set, which will cause this function
 * to only check the direct caller for privileges.
 */
int validate_stack(string priv, varargs int unguarded) {
   int i, sz, deny, privtype;
   mixed **stack;
   string progname, objname, funname, ppriv, opriv, tmp;
   mapping cache;

   if (!KERNEL() || !priv) {
      return 0;
   }

   privtype = query_priv_type(priv);
   stack = call_trace();

#ifdef DEBUG_STACK_SECURITY
   i = sizeof(stack)-5;
   if(i<0) i = 0;

   if(i == 0) {
      sz = 0;
   } else {
      sz = (stack[i][TRACE_FUNCTION] == "unguarded" && 
         stack[i][TRACE_PROGNAME] == AUTO);
   }

   DB( "validate_stack start : " + stack[i-sz][TRACE_PROGNAME] + ":" +
      stack[i-sz][TRACE_FUNCTION] + " called " + stack[i+1][TRACE_FUNCTION] +
      (sz ? " (unguarded)":"") + "\n"
   );
   switch(privtype & 0x1f) {
      case PT_UNKNOWN : tmp = "unknown";
                        break;
      case PT_PREDEF  : tmp = "predefined";
                        break;
      case PT_DOMAIN  : tmp = "domain";
                        break;
      case PT_WIZARD  : tmp = "wizard";
                        break;
      case PT_PLAYER  : tmp = "player";
                        break;
   }
   tmp = "(" + tmp + (privtype & PF_ORPHAN ? ", orphaned":"") + 
      (privtype & PF_NO_ACCESS ? ", no_access":"") +
      (privtype & PF_NO_CHECK ? ", no_check":"") + ") ";

   DBD("require : " + priv + " " + tmp + "\n");
#endif

   /* always allow */
   if (privtype & PF_NO_CHECK) {
      DB("validate_stack finish : allow\n");
      return 1;
   }

   /* no access */
   if (privtype & PF_NO_ACCESS) {
      DB("validate_stack finish : deny\n");
      return 0;
   }

   /* privilege exists but is orphaned */
   if (privtype & PF_ORPHAN) {
      console_msg(object_name(previous_object()) + " used orphaned privilege " +
         priv + "\n");

   /* never heard about this privilege */
   } else if (privtype == PT_UNKNOWN) {
      error("Unknown privilege " + priv);
   }

   cache = DRIVER->get_tlvar(TLS_CACHE);
   if (!cache) cache = ([]);

   for (i = sizeof(stack) - 4; (i >= 0) && !deny && (unguarded < 2); i--) {
      progname = stack[i][TRACE_PROGNAME];
      objname = stack[i][TRACE_OBJNAME];
      funname = stack[i][TRACE_FUNCTION];

      if (unguarded || ((funname == "unguarded")
         && (sscanf(progname, "/kernel/lib/auto%*s")))) {
         unguarded++;
      }

      if (cache[objname]) {
         opriv = cache[objname];
      } else {
         opriv = determine_obj_privs(objname);
         cache[objname] = opriv;
      }

      ppriv = determine_program_privs(progname);

      DBD("frame " + i + ": program  : " + progname + ":" + funname + "\n");
      DBD("frame " + i + ": privs    : " + ppriv + "\n");
      DBD("frame " + i + ": object   : " + objname + "\n");
      DBD("frame " + i + ": privs    : " + opriv + "\n");

      if (!validate_privilege(ppriv, priv)) {
         deny++;
      }

      if (!validate_privilege(opriv, priv)) {
         deny++;
      }
   }
   DRIVER->set_tlvar(TLS_CACHE,cache);
   DB("validate_stack finish : " + (!deny ? "allow":"deny")+"\n");
   return !deny;
}

/*
 * Determine the privilege required for reading the file provided as argument.
 * It does not check at all if that file exists!
 */
string query_read_priv(string file) {
   string *parts;

   parts = explode(file, "/");

#ifdef DEBUG_PRIVS
   console_msg("query_read_priv( \"" + file + "\" )\n");
#endif

   if (!sizeof(parts)) {
      return "*";
   }

   /*
    * domains dir is special. Read access to everything for
    * everyone except for the /domains/<dom>/data dir.
    *
    * daemons dir is special. Read access to everything for
    * everyone except for the /daemons/data dir.
    */
   switch (parts[0]) {
      case "kernel":
         if (sizeof(parts) > 1 && parts[1] == "data") {
            return owner_file(file);
         }
         /* fall through, so no I didn't forget a break here */
      case "domains":
         if (sizeof(parts) > 2 && parts[2] == "data") {
            return owner_file(file);
         }
         break;
      case "data":
         return owner_file(file);
         break;
      case "daemons":
      case "sys":
         if ((sizeof(parts) > 1 && parts[1] == "data") || (sizeof(parts) > 2
            && parts[2] == "data")) {
            return owner_file(file);
         }
         break;
      case "wiz":
         if (sizeof(parts) > 1) {
            return owner_file(file);
         }
         break;
   }

   return "*";
}

/*
 * Determine the privilege required for writing the file provided as
 * argument.
 */
string query_write_priv(string file) {
   string owner;

#ifdef DEBUG_PRIVS
   console_msg("query_write_priv( \"" + file + "\" )\n");
#endif

   owner = owner_file(file);
#ifdef SECURITY_RO_KERNEL
   if (owner == "kernel") {
      return "-";
   }
#endif
   return owner;
}


/* invalidate privilege cache */
void invalidate_pcache(void) {
   if(previous_program() == "/sys/lib/runas") {
      DRIVER->set_tlvar(TLS_CACHE, ([ ]));
   }
}
