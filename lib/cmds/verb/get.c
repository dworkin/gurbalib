void usage() {
   write("Usage: get [-h] [all|OBJ]\n");
   write("Allows you to pick up a given object OBJ.\n");
   write("Options:\n");
   write("\tall\tPick's up everything you can pick up.\n");
   write("Examples:\n");
   write("\tget sword\n");
   write("\tget all\n");
   write("\tget potion from table\n");
}

string *query_verb_info() {
   return (( { "", "OBJE", "LIV", "OBJX from OBJ", "OBJA" } ));
}

int can_get() {
   return 1;
}

int can_get_str(string str) {
   return 1;
}

int can_get_obj(object obj) {
   return 1;
}

int can_get_liv(object liv) {
   return 1;
}

int can_get_obj_str_obj(object target, string s, object obj) {
   return 1;
}

int can_get_str_str_obj(string target, string s, object obj) {
   return 1;
}

void do_get() {
   write("Get what?");
}

void do_get_str(string str) {
   object *inv;
   int i;
   string name;

   if (lowercase(str) != "all" && lowercase(str) != "everything") {
      write("You can't seem to find the " + str + ".");
      return;
   }

   inv = this_environment()->query_inventory();
   for (i = 0; i < sizeof(inv); i++) {
      if (inv[i]->is_gettable()) {
         if (inv[i]->is_money()) {
            name = inv[i]->query_id();
         }
	 if (inv[i]->move(this_player())) {
            if (name && (name != "")) 
               this_player()->targetted_action("$N $vpick up some coins.", nil);
            else 
               this_player()->targetted_action("$N $vpick up $o.", nil, inv[i]);
	 } else {
	    this_player()->targetted_action(
               "$N $vtry to pick up $o, but $vfail.", nil, inv[i]);
	 }
      } else {
	 if (!inv[i]->is_player()) {
	    this_player()->targetted_action("$N $vare unable to get $o.", nil,
	       inv[i]);
	 }
      }
   }
}

void do_get_obj(object obj) {
   string name;

   if (!obj->is_gettable()) {
      write("You can't get the " + obj->query_id() + ".");
      return;
   }
   if (obj->is_money()) {
      name = obj->query_id();
   }
   if (obj->move(this_player())) {
      if (name && (name != ""))
         this_player()->targetted_action("$N $vpick up some coins.", nil);
      else
         this_player()->targetted_action("$N $vpick up $o.", nil, obj);
   } else {
      this_player()->targetted_action("$N $vtry to pick up $o, but $vfail.",
	 nil, obj);
   }
}

void do_get_liv(object obj) {
   write("You can't get that.");
}

void do_get_obj_str_obj(object target, string s, object obj) {
   if (s == "from" && obj->is_container()) {
      if (obj->is_closed()) {
	 write("It's closed.");
	 return;
      }
   } else {
      write("You can't get " + target->query_id() + " from " + obj->query_id() +
	 ".");
      return;
   }
   if (target->move(this_player())) {
      this_player()->targetted_action("$N $vget $o from $o1.", nil, target,
	 obj);
   } else {
      this_player()->
	 targetted_action("$N $vtry to get $o from $o1, but $vfail.", nil,
	 target, obj);
   }
}

void do_get_str_str_obj(string target, string s, object obj) {
   object *inv;
   int i;

   if (target != "all" && target != "everything") {
      write("You don't see any " + target + " in the " + obj->query_id() + ".");
      return;
   }

   inv = obj->query_inventory();
   if (!inv || (sizeof(inv) == 0)) {
      write("There is nothing in the " + obj->query_id() + ".");
      return;
   }

   for (i = 0; i < sizeof(inv); i++) {
      if (inv[i]->move(this_player())) {
	 this_player()->targetted_action("$N $vget $o from $o1.", nil, inv[i],
	    obj);
      } else {
	 this_player()->
	    targetted_action("$N $vtry to get $o from $o1, but $vfail.", nil,
	    inv[i], obj);
      }
   }
}
