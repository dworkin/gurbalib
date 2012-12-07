object *storage;
int storage_size;

int is_storage(void) {
   return 1;
}

void set_storage_size(int size) {
   storage_size = size;
}

object find_stored_object(string name) {
   int i, j;
   string *ids;
   for (i = 0; i < sizeof(storage); i++) {
      ids = storage[i]->query_ids();
      if (ids) {
	 for (j = 0; j < sizeof(ids); j++) {
	    if (lowercase(ids[j]) == lowercase(name))
	       return (storage[i]);
	 }
      }
   }
   return nil;
}

void store_object(object ob) {
   if (!storage)
      storage = ( { } );

   if (sizeof(storage) >= storage_size) {
      this_player()->write("The storage is full.\n");
      return;
   }

   storage += ( { ob } );

   if (ob->is_worn()) {
      this_player()->do_remove(ob);
      this_player()->targetted_action(ob->query_remove_message(), nil, ob);
   }

   if (ob->is_wielded()) {
      this_player()->do_unwield(ob);
      this_player()->targetted_action(ob->query_unwield_message(), nil, ob);
   }

   if (ob->is_gettable()) {
      ob->set_environment(nil);
      if (this_player()->remove_object(ob)) {
	 this_player()->targetted_action("$N $vstore $o.", nil, ob);
      } else {
	 this_player()->targetted_action("$N $vtry to store $o, but $vfail.",
	    nil, ob);
      }
   } else {
      this_player()->targetted_action("$N $vare unable to store $o.", nil, ob);
   }
}

void borrow_object(string name) {
   object ob;

   ob = find_stored_object(name);
   if (!ob) {
      this_player()->write("You can't seem to find the " + lowercase(name) +
	 ".\n");
      return;
   }

   storage -= ( { ob } );
   if (ob->is_gettable()) {
      ob->set_environment(nil);
      if (ob->move(this_player())) {
	 this_player()->targetted_action("$N $vborrow $o.", nil, ob);
      } else {
	 this_player()->targetted_action("$N $vtry to borrow $o, but $vfail.",
	    nil, ob);
      }
   } else {
      this_player()->targetted_action("$N $vare unable to borrow $o.", nil, ob);
   }
}

string query_stored_list(void) {
   string msg;
   int i;

   if (!storage)
      storage = ( { } );

   if (sizeof(storage) == 0) {
      return " \nThe storage is empty.\n";
   } else {
      msg = " \nThe storage contains the following:\n";
      for (i = 0; i < sizeof(storage); i++) {
	 msg += "  " + storage[i]->query_id() + "\n";
      }
      msg += "\n";
      return msg;
   }
}
