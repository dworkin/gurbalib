#define PLAYER_L 0
#define WIZ_L    1
#define ADMIN_L  2

#define DMEMBER  1
#define DADMIN   2

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

int add_domain(string name) {
   if (!require_priv("system")) {
      error("Illegal call to add_domain");
   }

   if (!domains[name]) {
      domains[name] = ([]);
      if(find_object(BANISH_D)) {                                            
         BANISH_D->create();                                                 
      }                               
      save_me();
      return 1;
   } else {
      return 0;
   }
}

int remove_domain(string name) {
   if (!require_priv("system")) {
      error("Illegal call to remove_domain");
   }

   if (domains[name] != nil) {
      domains[name] = nil;
      save_me();
      return 1;
   } else {
      return 0;
   }
}

void mkdomains() {
   int i, sz;
   string *names;

   names = get_dir(DOMAINS_DIR + "/*")[0];
   names -= ( { ".", "..", ".svn", ".cvs" } );
   for (i = 0, sz = sizeof(names); i < sz; i++) {
      unguarded("add_domain", names[i]);
   }
}

int is_domain(string name) {
   return domains[name] != nil;
}

int add_domain_member(string domain, string member) {
   if (!require_priv("system")) {
      error("Illegal call to add_domain_member");
   }

   if (is_domain(domain)) {
      if (!mappingp(domains[domain])) {
         domains[domain] = ([]);
      }
      if (!domains[domain][member]) {
         domains[domain][member] = DMEMBER;
         save_me();
         return 1;
      }
   }
}

int remove_domain_member(string domain, string member) {
   /* note, people are allowed to remove themselves from a domain */
   if (!require_priv("system") && !require_priv(member)) {
      error("Illegal call to remove_domain_member");
   }

   if (is_domain(domain)) {
      if (mappingp(domains[domain])) {
         domains[domain][member] = nil;
         save_me();
         return 1;
      }
   }
}

int promote_domain_member(string domain, string member) {
   if(!require_priv("system")) {
      error("Illegal call to promote_domain_member");
   }
   domains[domain][member] = DADMIN;
   save_me();
   return 1;
}

int demote_domain_member(string domain, string member) {
   if(!require_priv("system")) {
      error("Illegal call to promote_domain_member");
   }
   domains[domain][member] = DMEMBER;
   save_me();
   return 1;
}

int query_domain_member(string domain, string member) {
   return (domains[domain] && mappingp(domains[domain]) && 
      domains[domain][member]);
}

int query_domain_admin(string domain, string member) {
   return (domains[domain] && mappingp(domains[domain]) && 
      domains[domain][member] == DADMIN);
}

string *query_domain_members(string domain) {
   return (domains[domain] && mappingp(domains[domain])) ? 
      map_indices(domains[domain]) : ({ });
}

string *query_domains() {
   return map_indices(domains);
}

string *query_wizards() {
   return filter_array(map_indices(privs), "query_wiz", this_object());
}

string *known_names() {
   string *result;
   result = SYS_BANNED_NAMES;
   result |= query_domains();
   result |= query_wizards();
   return result;
}

int query_priv_type(string p) {
   int r;

   if (sizeof(SECURITY_NO_CHECK & ({ p }))) {
      r = PT_PREDEF | PF_NO_CHECK;
   } else if (sizeof(SECURITY_NO_ACCESS & ({ p }))) {
      r = PT_PREDEF | PF_NO_ACCESS;
   } else if (sizeof(SYS_BANNED_NAMES & ({ p }))) {
      r = PT_PREDEF;
   } else if (domains[p]) {
      if (file_exists(DOMAINS_DIR + "/" + p) != 0) {
         r = PT_DOMAIN;
      } else {
         r = PT_DOMAIN_BAD;
      }
   /* note, there is nothing special about the privilege with the 
      name of an admin */
   } else if (privs[p] == WIZ_L || privs[p] == ADMIN_L) {
      if (file_exists("/data/players/" + p + ".o") == 1) {
         r = PT_WIZARD;
      } else {
         r = PT_WIZARD_BAD;
      }
   } else if (privs[p] == PLAYER_L) {
      if (file_exists("/data/players/" + p + ".o") == 1) {
         r = PT_PLAYER;
      } else {
         r = PT_PLAYER_BAD;
      }
   } else {
      if (file_exists("/data/players/" + p + ".o") == 1) {
         r = PT_PLAYER;
         privs[p] = PLAYER_L;
      } else {
         r = PT_UNKNOWN;
      }
   }
   return r;
}

static void create(void) {
   privs = ([]);
   domains = ([]);
   if (!restore_me()) {
      mkdomains();
   }
   DRIVER->register_secure_d();
}

void create_homedir(string wiz) {
   string path;

   if (!require_priv("system")) {
      error("Access denied");
   }

   path = WIZ_DIR + "/" + wiz + "/";

   if (file_exists(path) == 0) {
      make_dir(path);
      make_dir(path + "rooms/");
      copy(DOMAINS_DIR + "/required/rooms/workroom.c", 
         path + "rooms/workroom.c");
   }
}

void delete_homedir(string wiz) {
   string path;

   if (!require_priv("system")) {
      error("Access denied");
   }

   path = WIZ_DIR + "/" + wiz + "/";

   if (file_exists(path) == 0) {
      error("No such directory: " + path + "\n");
   } else {
      if (remove_dir(path)) {
	 write("Ok.\n");
      } else {
	 write("Failed to remove: " + path + "\n");
      }
   }
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

void make_mortal(string name) {
   object player;
   string prev;

   prev = previous_object()->base_name();
   if (prev != "/sys/cmds/admin/promote") {
      error("Hey! No cheating!\n" + prev + " != /sys/cmds/admin/promote\n");
      LOG_D->write_log("cheating", "Player: " + this_player()->query_Name() + 
         " was trying to make_mortal(" + name + ") with this object " + 
         prev + "\n");
   }

   if (!require_priv("system")) {
      error("Access denied");
   }

   name = lowercase(name);
   if (file_exists("/data/players/" + name + ".o")) {
      privs[name] = PLAYER_L;
      player = USER_D->find_player(name);
      if (!player) {
	 /* Player not active now, load him in and add his paths. */
	 player = clone_object(PLAYER_OB);
	 player->set_name(name);
	 player->restore_me();
	 player->remove_channel("dgd");
	 player->remove_cmd_path("/sys/cmds/admin");
	 player->remove_cmd_path("/sys/cmds/wiz");
	 player->save_me();
	 destruct_object(player);
      } else {
	 player->remove_channel("dgd");
	 player->remove_cmd_path("/sys/cmds/admin");
	 player->remove_cmd_path("/sys/cmds/wiz");
	 player->save_me();
      }
      write(capitalize(name) + " has been made a mortal.");
      save_me();
   } else {
      write("No such player.\n");
   }
}

void make_wizard(string name) {
   object player;
   string prev;

   prev = previous_object()->base_name();
   if (prev != "/sys/cmds/admin/promote" &&
       prev != "/sys/daemons/user_d") {
      error("Hey! No cheating!\n" + prev + " != /sys/cmds/admin/promote\n");
      LOG_D->write_log("cheating", "Player: " + this_player()->query_Name() + 
         " was trying to make_wizard(" + name + ") with this object " + 
         prev + "\n");
   }

   if (!require_priv("system")) {
      error("Access denied");
   }

   name = lowercase(name);
   if (file_exists("/data/players/" + name + ".o")) {
      privs[name] = WIZ_L;
      player = USER_D->find_player(name);
      if (!player) {
	 /* Player not active now, load him in and add his paths. */
	 player = clone_object(PLAYER_OB);
	 player->set_name(name);
	 player->restore_me();
	 player->remove_channel("dgd");
	 player->remove_cmd_path("/sys/cmds/admin");
	 player->add_cmd_path("/sys/cmds/wiz");
	 player->save_me();
	 destruct_object(player);
      } else {
	 player->remove_channel("dgd");
	 player->remove_cmd_path("/sys/cmds/admin");
	 player->add_cmd_path("/sys/cmds/wiz");
	 player->save_me();
      }
      unguarded("create_homedir", name);
      write(capitalize(name) + " has been made a wizard.");
      save_me();
   } else {
      write("No such player.\n");
   }
}

void make_admin(string name) {
   object player;
   string prev;

   prev = previous_object()->base_name();
   if (prev != "/sys/cmds/admin/promote" && 
       prev != "/kernel/daemons/secure_d") {
      error("Hey! No cheating!\n" + prev + " != /sys/cmds/admin/promote\n");
      LOG_D->write_log("cheating", "Player: " + this_player()->query_Name() + 
         " was trying to make_admin(" + name + ") with this object " + 
         prev + "\n");
   }

   if (!require_priv("system")) {
      error("Access denied");
   }

   name = lowercase(name);
   if (file_exists("/data/players/" + name + ".o")) {
      privs[name] = ADMIN_L;
      player = USER_D->find_player(name);
      if (!player) {
	 /* Player not active now, load him in and add his paths. */
	 player = clone_object(PLAYER_OB);
	 player->set_name(name);
	 player->restore_me();
	 player->add_cmd_path("/sys/cmds/wiz");
	 player->add_cmd_path("/sys/cmds/admin");
	 player->add_channel("dgd");
	 player->save_me();
	 destruct_object(player);
      } else {
	 player->add_cmd_path("/sys/cmds/wiz");
	 player->add_cmd_path("/sys/cmds/admin");
	 player->add_channel("dgd");
	 player->save_me();
      }
      unguarded("create_homedir", name);
      write(capitalize(name) + " has been made an admin.");
      save_me();
   } else {
      write("No such player.\n");
   }
}

int query_admin(string name) {
   if (privs[name] == ADMIN_L) {
      return 1;
   }
   return 0;
}

int query_wiz(string name) {
   if (privs[name] == ADMIN_L || privs[name] == WIZ_L) {
      return 1;
   }
   return 0;
}

int query_mortal(string name) {
   return ((privs[name] != ADMIN_L) && (privs[name] != WIZ_L));
}

int query_priv(string name) {
   if (map_sizeof(privs) == 0) {
      unguarded("make_admin", name);
   }
   if (!privs[name]) {
      return 0;
   }
   return privs[name];
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
      case "domains":
	 if (sizeof(parts) > 1) {
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
      /* 
       * unknown location, explicitly return an unknown priv to trigger 
       * a warning or error depending on SECURITY_NO_UNKNOWN_PRIV 
       */
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

   if (!ob) {
      return ":nobody:";
   }

   if (sscanf(objname, "/sys/obj/user#%*s") == 1 || 
      (ob <- "/sys/obj/player")) {
      if (ob <- "/sys/obj/player") {
	 object u;

	 u = ob->query_user();
	 if (u && u->query_player() == ob) {
	    name = u->query_name();
	 }
      } else {
	 name = ob->query_name();
      }

      if (!name || name == "") {
	 priv = "nobody";
      } else {
         int di, dsz;
         string *dn;

	 priv = name;
	 if (query_wiz(name)) {
	    priv += ":wizard";
	 }

	 if (query_admin(name)) {
	    priv += ":system";
	 }
         dn = query_domains();
         for (di=0, dsz=sizeof(dn); di<dsz; di++) {
            if (query_domain_member(dn[di],name)) {
               priv += ":"+dn[di];
            }
         }
      }

      if (ob <- "/sys/obj/player") {
	 priv += ":game";
      }
   } else {
      priv = owner_file(objname);
   }

   return ":" + priv + ":";
}

/*
 * The stack validator, this function is what it is all about..
 *
 * Gets a call_stack, and loops through it to determine the 
 * privileges of all objects and inheritables that brought us
 * to where we are now. It then matches those privileges against
 * the required privilege provided in the priv argument.
 * Optionally, unguarded can be set, which will cause this function
 * to only check the direct caller for privileges.
 */

static int validate_privilege(string spriv, string rpriv) {
   if (root_priv(spriv) ||
      (game_priv(spriv) && is_domain(rpriv)) ||
      (sscanf(spriv, "%*s:" + rpriv + ":%*s") != 0)) {
      return 1;
   }
}

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

   if(i == 0) 
      sz = 0;
   else
      sz = (stack[i][TRACE_FUNCTION] == "unguarded" && 
         stack[i][TRACE_PROGNAME] == AUTO);

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
      error("Orphaned privilege " + priv);
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
#ifdef DEBUG_PRIVS
   console_msg("query_write_priv( \"" + file + "\" )\n");
#endif
   return owner_file(file);
}

static void upgraded() {
   if (!domains) {
      domains = ([]);
      mkdomains();
   }
}
