#define AUTH_DATA "/sys/daemons/auth_data"
#define CACHE_INTERVAL 300
#define AUTH_DATA_DIR "/sys/daemons/data/users"

static mapping users;
static mapping cache;
static object *pool;
static object spare;

int data_version;

static void secure() {
   string name;

   name = previous_program(1);
   if ((name != USER_OB) && !require_priv("system")) {
      error("Access denied: " + name + "\n");
   }
}

static void save_me() {
   unguarded("save_object", "/sys/daemons/data/user_d.o");
}

static void restore_me() {
   unguarded("restore_object", "/sys/daemons/data/user_d.o");
}

int logout(string name) {
   object ob;

   secure();

   ob = cache[name];

   if (ob) {
      if (!spare) {
	 spare = ob;
	 cache[name] = nil;
      } else {
	 destruct_object(ob);
      }
      return 1;
   } else {
      return 0;
   }
}

object find_user(string name) {
   string *names;
   int i, sz, found;

   found = 0;
   names = map_indices(users);
   for (i = 0, sz = sizeof(names); i < sz; i++) {
      if (name == names[i]) {
	 found = 1;
	 break;
      }
   }

   if (found == 1) {
      return users[name];
   } else {
      return nil;
   }
}

/*
 * If there are any data objects (clones) around, destruct them.
 *
 */
static void cleanup() {
   object c, n;

   c = find_object(AUTH_DATA);
   if (!c) {
      return;
   }

   c = c->next_clone();

   while (c) {
      n = c->next_clone();
      if (c == spare) {
	 spare = nil;
      }
      destruct_object(c);
      c = n;
   }
}

static void create() {
   object *u;
   int i, sz;

   cache = ([]);
   restore_me();

   if (!data_version) {
      call_out("convert_users", 0);
   }

   users = ([]);

   u = users();

   for (i = 0, sz = sizeof(u); i < sz; i++) {
      if (u[i]->query_name() && u[i] <-USER_OB) {
	 users[u[i]->query_name()] = u[i];
      }
   }

   call_out("clean_cache", CACHE_INTERVAL);
   cleanup();
}

static object get_data_ob(string name) {
   object ob;

   ob = cache[name];

   if (ob) {
      return ob;
   }

   if (spare) {
      ob = spare;
      spare = nil;
   } else {
      ob = clone_object(AUTH_DATA);
   }

   if (ob->load(name)) {
      cache[name] = ob;
      return ob;
   } else {
      if (!spare) {
	 spare = ob;
      } else {
	 destruct_object(ob);
      }
   }
}

static void clean_cache() {
   int i, sz;
   string *names;

   names = map_indices(cache);

   for (i = 0, sz = sizeof(names); i < sz; i++) {
      if (!USER_D->find_user(names[i])) {
	 logout(names[i]);
      }
   }

   call_out("clean_cache", CACHE_INTERVAL);
}

int set_password(string name, string secret) {
   object data;

   secure();

   data = get_data_ob(name);

   if (!data) {
      return 0;
   }
   data->set_pass(name,secret);
   save_me();
}

int reset_password(string who, string passwd) {
   object obj;

   if (!query_admin(this_player())) {
      return 0;
   }

   obj = USER_D->find_player(who);
   if (obj) {
      write("That user is currently logged in you cannot change their " +
         "password.\n");
   }

   obj = get_data_ob(who);
   if (!obj) {
      return 0;
   }
   obj->set_pass(who,passwd);
   obj->save_me();
   destruct_object(obj);
   return 1;
}

int login(string name, string secret) {
   object data;

   secure();

   data = get_data_ob(name);

   if (!data) {
      return 0;
   }

   return data->test(name, secret);
}

int user_exists(string name) {
   return unguarded("file_exists", AUTH_DATA_DIR + "/" + name + ".o") == 1;
}

static int _new_user(string name, string secret) {
   object ob;

   if (spare) {
      ob = spare;
      spare = nil;
   } else {
      ob = clone_object(AUTH_DATA);
   }

   ob->set_name(name);
   ob->set_pass(name,secret);

   return 1;
}

int new_user(string name, string secret) {
   int result;
   secure();

   unguarded("_new_user", name, secret);

   #ifdef ALL_USERS_WIZ
      if (!SECURE_D->make_wizard(name)) {
         write("Error calling make_wizard(name)\n");
      }
   #endif
   
   return 1;
}

int _delete_user(string name) {
   object u, p;

   if (!require_priv("system")) {
      error("Access denied.");
      return 0;
   }

   if (u = find_user(name)) {
      p = u->query_player();
      destruct_object(u);
      if (p) {
	 destruct_object(p);
      }
   }

   if (cache[name]) {
      if (!spare) {
	 spare = cache[name];
      } else {
	 destruct_object(cache[name]);
      }
      cache[name] = nil;
   }

   LAST_D->remove_entry(name);

   unguarded("remove_file", AUTH_DATA_DIR + "/" + name + ".o");
   unguarded("remove_file", "/data/players/" + name + ".o");

   return 1;
}

int delete_user(string name) {
   secure();

   return unguarded("_delete_user", name);
}

static void convert_users() {
   string *names;
   int i, sz;
   object c;

   names = get_dir("/data/players/*.o")[0];
   c = clone_object(AUTH_DATA);

   rlimits(MAX_DEPTH; -1) {
      for (i = 0, sz = sizeof(names); i < sz; i++) {
	 string n;

	 sscanf(names[i], "%s.o", n);
	 c->convert_user(n);
      }
   }
   data_version = 1;
   save_me();
   destruct_object(c);
}

static void destructing() {
   cleanup();
}

void user_online(string name, object user) {
 users += ([name:user]);
}

void user_offline(string name, object user) {
   users[name] = nil;
   unguarded("logout", name);
}

object *query_users(void) {
   return (map_values(users));
}

string *query_user_names(void) {
   return (map_indices(users));
}

object find_player(string name) {
   object ob;
   ob = find_user(lowercase(name));
   if (ob)
      return (ob->query_player());
   return (ob);
}

object *query_players(void) {
   object *usr;
   int i, sz;
   object *players;

   usr = query_users();

   players = ( { } );

   for (i = 0, sz = sizeof(usr); i < sz; i++) {
      players += ( { usr[i]->query_player() } );
   }
   return players;
}

object *query_wizards(void) {
   object *usr;
   int i, sz;
   object *wizards;

   usr = query_users();

   wizards = ( { } );

   for (i = 0, sz = sizeof(usr); i < sz; i++) {
      if (query_wizard(usr[i]->query_player()->query_name()) > 0) {
	 wizards += ( { usr[i]->query_player() } );
      }
   }
   return wizards;
}

int valid_player_name(string str) {
   return !catch(parse_string("valid=/[a-zA-Z][a-zA-Z0-9]+/ name: valid", str));
}

int player_exists(string str) {
   return unguarded("file_exists", "/data/players/" + str + ".o") > 0;
}

string *list_all_users() {
   string *names;
   string *files;
   string name;
   int x, i;

   names = ( { } );
   files = get_dir("/data/players/*.o")[0];

   for (i = sizeof(files) - 1; i >= 0; i--) {
      x = strlen(files[i]) - 3;
      name = files[i][..x];
      names += ( { name } );
   }

   return names;
}

void upgraded() {
   object *u;
   int i, sz;

   if (pool) {
      for (i = 0, sz = sizeof(pool); i < sz; i++) {
	 if (i == 0) {
	    spare = pool[i];
	 } else if (objectp(pool[i])) {
	    destruct_object(pool[i]);
	 }
      }
      pool = nil;
   }

   if (!users) {
      users = ([]);
      u = users();
      for (i = 0, sz = sizeof(u); i < sz; i++) {
	 if (u[i]->query_name() && u[i] <-USER_OB) {
	    users[u[i]->query_name()] = u[i];
	 }
      }
   }
}

void print_finger_info(object player, object player2, int cloned) {
   player->message("%^BLUE%^Name:%^RESET%^ " + player2->query_Name() + "\n");
   player->message("%^BLUE%^Title:%^RESET%^ " + player2->query_title() + "\n");
   if (query_admin(player2->query_name()) == 1) {
      player->message("%^BLUE%^Status: %^RESET%^Administrator\n");
   } else if (query_wizard(player2->query_name()) == 1) {
      player->message("%^BLUE%^Status: %^RESET%^Wizard\n");
   } else {
      player->message("%^BLUE%^Status: %^RESET%^Player\n");
   }
   player->message("%^BLUE%^Age:%^RESET%^ " + player2->query_age() + "\n");

   if (query_wizard(player)) {
      player->message("%^BLUE%^Description:%^RESET%^ " +
	 player2->query_long() + "\n");
   }

   if (query_admin(player)) {
      if (player2->query_real_name()) {
         player->message("%^BLUE%^Real name: %^RESET%^" +
	    player2->query_real_name() + "\n");
      } else {
         player->message("%^BLUE%^Real name: %^RESET%^\n");
      }
      if (player2->query_email_address()) {
         player->message("%^BLUE%^Email address: %^RESET%^" +
	    player2->query_email_address() + "\n");
      } else {
         player->message("%^BLUE%^Email address: %^RESET%^\n");
      }
   }

   if (cloned == 1) {
      player->message("%^BLUE%^Last login: %^RESET%^" +
	 ctime(player2->query_last_login()));
   } else {
      player->message("%^BLUE%^Last login: %^RESET%^Now\n");
      if (player2->query_idle() > 60) {
	 player->message("%^BLUE%^Idle: %^RESET%^" +
	    format_time(player2->query_idle()) + "\n");
      }
   }
}

/* Player is requesting finger information on player: name
   So lets tell them....  return 0 if not found. 1 if telling player info...
*/
void finger(object player, string name) {
   object obj;

   obj = find_player(name);
   if (!obj) {
      obj = get_data_ob(name);
      if (obj) {
	 obj = clone_object(PLAYER_OB);
	 obj->set_name(name);
	 obj->restore_me();

	 print_finger_info(player, obj, 1);
	 destruct_object(obj);
      }
   } else {
      print_finger_info(player, obj, 0);
   }
}

string print_email_info(object player, object obj, string type) {
   string str;
   int doit;

   doit = 0;
   if (type == "wizards") {
      if (USER_D->query_wizard(obj)) doit = 1;
      else doit = 0;
   } else if (type == "admins") {
      if (USER_D->query_admin(obj)) doit = 1;
      else doit = 0;
   } else {
      doit = 1;
   }

   if (doit) {
      if (obj->query_real_name()) {
         str = obj->query_real_name();
      } else {
         str = "";
      }
      if (obj->query_name()) {
         str += "(" + obj->query_name() + ") <" ;
      } else {
         str += "() <";
      }
      if (obj->query_email_address()) {
         str += obj->query_email_address() + ">";
      } else {
         str += ">";
      }
   }

   return str;
}

string get_email_info(object player, string name, string type) {
   object obj;
   string stuff;

   obj = find_player(name);
   if (!obj) {
      obj = clone_object(PLAYER_OB);
      obj->set_name(name);
      obj->restore_me();

      stuff = print_email_info(player, obj, type);
      destruct_object(obj);
   } else {
      stuff = print_email_info(player, obj, type);
   }

   return stuff;
}
