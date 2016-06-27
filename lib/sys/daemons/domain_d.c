/* Gurbalib's domain daemon Sept 2013, Aidil@Way of the Force */

#define DMEMBER  1
#define DADMIN   2

mapping domains;

static int restore_me(void) {
   return restore_object("/sys/daemons/data/domain_d.o");
}

static void save_me(void) {
   save_object("/sys/daemons/data/domain_d.o");
}

static void mkdomains(void) {
   int i, sz;
   string *names;

   domains = ([ ]);
   names = unguarded("get_dir", DOMAINS_DIR + "/*")[0];
   names -= ( { ".", "..", ".svn", ".cvs" } );
   for (i = 0, sz = sizeof(names); i < sz; i++) {
      unguarded("add_domain", names[i]);
   }
}

void create(void) {
   if (!unguarded("restore_me")) {
      domains = SECURE_D->query_domain_data();
      unguarded("save_me");
   }

   if (!domains) {
      mkdomains();
   }
}

int add_domain(string name) {
   string prev;

   if (!require_priv("system")) {
      prev = previous_object()->base_name();
      error("Illegal call to add_domain: " + prev + "\n");
   }

   if (!member_map(name, domains)) {
      domains[name] = ([]);
      if (find_object(BANISH_D)) {
         BANISH_D->create();
      }
      save_me();
      return 1;
   } else {
      return 0;
   }
}

int remove_domain(string name) {
   string prev;

   if (!require_priv("system")) {
      prev = previous_object()->base_name();
      error("Illegal call to remove_domain: " + prev + "\n");
   }

   if (domains[name] != nil) {
      domains[name] = nil;
      save_me();
      return 1;
   } else {
      return 0;
   }
}

int is_domain(string name) {
   return domains[name] != nil;
}

int add_domain_member(string domain, string member) {
   string prev;

   if (!require_priv("system")) {
      prev = previous_object()->base_name();
      error("Illegal call to add_domain_member: " + prev + "\n");
   }

   if (is_domain(domain)) {
      if (!mappingp(domains[domain])) {
         domains[domain] = ([]);
      }
      if (!domains[domain][member]) {
         domains[domain][member] = DMEMBER;
         save_me();
         USER_D->restore_privs(member);
         return 1;
      }
   }
}

int remove_domain_member(string domain, string member) {
   string prev;

   /* note, people are allowed to remove themselves from a domain */
   if (!require_priv("system") && !require_priv(member)) {
      prev = previous_object()->base_name();
      error("Illegal call to remove_domain_member: " + prev + "\n");
   }

   if (is_domain(domain)) {
      if (mappingp(domains[domain])) {
         domains[domain][member] = nil;
         save_me();
         USER_D->restore_privs(member);
         return 1;
      }
   }
}

int promote_domain_member(string domain, string member) {
   string prev;

   if (!require_priv("system")) {
      prev = previous_object()->base_name();
      error("Illegal call to promote_domain_member: " + prev + "\n");
   }
   domains[domain][member] = DADMIN;
   save_me();
   return 1;
}

int demote_domain_member(string domain, string member) {
   string prev;

   if (!require_priv("system")) {
      prev = previous_object()->base_name();
      error("Illegal call to demote_domain_member: " + prev + "\n");
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
   if (domains[domain] && mappingp(domains[domain])) {
      return map_indices(domains[domain]);
   }

   return ({ });
}

string *query_domains(void) {
   return map_indices(domains);
}

