static mapping objs;
static mapping clones;

void create(void) {
   objs = ([]);
   clones = ([]);
}

void register_object(object ob) {
   string owner;

   owner = owner_object(ob);
   if (!owner) {
      owner = "<none>";
   }

   if (!objs[owner]) {
      objs[owner] = ([]);
   }

   objs[owner][ob] = 0;
}

void unregister_object(object ob) {
   string owner;

   owner = owner_object(ob);
   if (!owner) {
      owner = "<none>";
   }

   if (!objs[owner]) {
      return;
   }

   objs[owner][ob] = nil;
   if (!map_sizeof(objs[owner])) {
      objs[owner] = nil;
   }
}

void register_clone(object ob) {
   string cloner;

   cloner = ob->query_cloner();
   if (!cloner) {
      cloner = "nobody";
   }

   if (clones[cloner] == nil) {
      clones[cloner] = 0;
   }

   clones[cloner]++;
}

void unregister_clone(object ob) {
   string cloner;

   cloner = ob->query_cloner();
   if (!cloner) {
      cloner = "nobody";
   }

   if (clones[cloner] == nil) {
      return;
   }

   clones[cloner]--;
   if (clones[cloner] < 0) {
      console_msg("Clone count going negative for " + cloner + "\n");
      clones[cloner] = 0;
   }
}

int query_number_objects(void) {
   int total, i, sz;
   string *keys;

   total = 0;
   keys = map_indices(objs);

   for (i = 0, sz = sizeof(keys); i < sz; i++) {
      total += map_sizeof(objs[keys[i]]);
   }
   return total;
}

string *query_object_owners(void) {
   return (map_indices(objs));
}

object *query_objects_by_owner(string owner) {
   return objs[owner] ? map_indices(objs[owner]) : ( { } );
}

string *query_cloners() {
   return map_indices(clones);
}

int query_number_clones() {
   int total, i, sz;
   string *keys;

   total = 0;
   keys = map_indices(clones);

   for (i = 0, sz = sizeof(keys); i < sz; i++) {
      total += clones[keys[i]];
   }
   return total;
}

int query_number_clones_by_user(string user) {
   return clones[user];
}
