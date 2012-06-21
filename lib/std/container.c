#include <type.h>

inherit ob OBJECT;

static object *inventory;
static mapping inv_map;

void create(void) {
   ob::create();
   inventory = nil;
   inv_map = ([]);
}

int is_container(void) {
   return 1;
}

void object_arrived(object obj) {
   int amount;
   string type;

   if (obj->is_money() && this_object()->is_player()) {
       amount = obj->query_amount();
       type = obj->query_currency();
       this_player()->add_money(type, amount);
       obj->destruct();
   }
}

void object_removed(object obj) {

}

int receive_object(object "/std/object" obj) {
   if (!inv_map)
      inv_map = ([]);

   inv_map[obj] = time();

   object_arrived(obj);
   return 1;
}

int remove_object(object obj) {
   if (!inv_map)
      return 0;
   else
      inv_map[obj] = nil;
   object_removed(obj);
   return 1;
}

nomask object *query_inventory(void) {

   if (inv_map)
      return (map_indices(inv_map));
   return ( { } );
}

object find_object_num(string name, int num) {
   int i, j;
   string *ids;

   object *inv;
   inv = query_inventory();

   if (inv)
      for (i = 0; i < sizeof(inv); i++) {
	 ids = inv[i]->query_ids();
	 if (ids) {
	    for (j = 0; j < sizeof(ids); j++) {
	       if (lowercase(ids[j]) == lowercase(name)) {
		  num--;
		  if (num == 0)
		     return (inv[i]);
	       }
	    }
	 }
      }
}

object present(string name) {
   return (find_object_num(name, 1));
}

object find_adj_object_num(string adj, string name, int num) {
   int i, j, k;
   string *ids;
   string *adjs;
   object *inv;

   inv = query_inventory();

   for (i = 0; i < sizeof(inv); i++) {
      ids = inv[i]->query_ids();
      if (ids) {
	 for (j = 0; j < sizeof(ids); j++) {
	    if (lowercase(ids[j]) == lowercase(name)) {
	       if (inv[i]->is_adj(adj) == 1) {
		  num--;
		  if (num == 0)
		     return inv[i];
	       }
	    }
	 }
      }
   }
   return nil;
}

object find_adj_object(string adj, string name) {
   return find_adj_object_num(adj, name, 1);
}

object find_adjs_object_num(string * adj, string name, int num) {
   int i, j, k;
   string *ids;
   string *adjs;
   object *inv;

   inv = query_inventory();

   for (i = 0; i < sizeof(inv); i++) {
      ids = inv[i]->query_ids();
      if (ids) {
	 for (j = 0; j < sizeof(ids); j++) {
	    if (lowercase(ids[j]) == lowercase(name)) {
	       int nFound;
	       nFound = 1;
	       for (k = 0; k < sizeof(adj); k++) {
		  if (!inv[i]->is_adj(adj[k]))
		     nFound = 0;
	       }
	       if (nFound) {
		  num--;
		  if (num == 0)
		     return inv[i];
	       }
	    }
	 }
      }
   }
   return nil;
}

object find_adjs_object(string * adj, string name) {
   return find_adjs_object_num(adj, name, 1);
}

void set_objects(mapping obs) {
   object ob;
   string *filename;
   string name;
   int i, j, num;
   object *inv;

   inv = query_inventory();

   filename = map_indices(obs);

   for (i = 0; i < sizeof(filename); i++) {
      if (strstr(filename[i], "#") != -1) {
	 name = filename[i][0..strstr(filename[i], "#") - 1];
      } else {
	 name = filename[i];
      }
      if (typeof(obs[filename[i]]) == T_ARRAY) {

	 ob = clone_object(name);
	 ob->move(object_name(this_object()));
	 ob->setup();
	 ob->mudlib_setup(obs[filename[i]]);
      } else {
	 num = obs[filename[i]];

	 for (j = 0; j < sizeof(inv); j++) {
	    if (inv[j]->base_name() == filename[i]) {
	       num--;
	    }
	 }

	 while (num > 0) {
	    ob = clone_object(name);
	    ob->move(object_name(this_object()));
	    ob->setup();
	    num--;
	 }
      }
   }
}

void move_or_destruct_inventory() {
   object dst, *items;
   int i, sz;

   items = query_inventory();

   dst = this_object()->query_environment();
   sz = sizeof(items);

   for (i = 0; i < sz; i++) {
      if (!dst || (items[i]->move(dst) != 1)) {
	 if (items[i]->is_player()) {
	    items[i]->move(VOID);
	 } else {
	    items[i]->destruct();
	 }
      }
   }
}

void upgraded() {
   int i, sz;

   if (inventory) {
      inventory -= ( { 0, nil } );

      inv_map = ([]);

      for (i = 0, sz = sizeof(inventory); i < sz; i++) {
	 inv_map[inventory[i]] = 1;
      }
      inventory = nil;
   }

   ::upgraded();
}
