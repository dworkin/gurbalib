void usage() {
   write("Usage: drop [-h] [all|OBJ]\n");
   write("Allows you to drop a given object OBJ.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tDrop everything your carrying.\n");
}

string *query_verb_info() {
   return (( { "", "OBJI", "OBJA" }));
}

int can_drop() {
   return 1;
}

int can_drop_str(string str) {
   return 1;
}

int can_drop_obj(object obj) {
   return 1;
}

void do_drop() {
   write("Drop what?");
}

void do_drop_str(string str) {
   object *inv;
   int i;

   if (lowercase(str) != "all" && lowercase(str) != "everything") {
      write("You can't seem to find the " + str + ".");
      return;
   }

   inv = this_player()->query_inventory();
   for (i = 0; i < sizeof(inv); i++) {
      if (inv[i]->is_worn()) {
	 this_player()->do_remove(inv[i]);
	 this_player()->targetted_action(inv[i]->query_remove_message(), nil,
	    inv[i]);
      }

      if (inv[i]->is_wielded()) {
	 this_player()->do_unwield(inv[i]);
	 this_player()->targetted_action(inv[i]->query_unwield_message(), nil,
	    inv[i]);
      }

      if (inv[i]->is_undroppable()) {
	 this_player()->targetted_action("$N $vare unable to drop $o.", nil,
	    inv[i]);
	 continue;
      }
      if (inv[i]->move(this_environment())) {
	 this_player()->targetted_action("$N $vdrop $o.", nil, inv[i]);
      } else {
	 this_player()->targetted_action("$N $vtry to drop $o, but $vfail.",
	    nil, inv[i]);
      }
   }
}

void do_drop_obj(object obj) {
   if (obj->is_undroppable()) {
      this_player()->targetted_action("$N $vare unable to drop $o.", nil, obj);
      return;
   }
   if (obj->is_worn()) {
      this_player()->do_remove(obj);
      this_player()->targetted_action(obj->query_remove_message(), nil, obj);
   }

   if (obj->is_wielded()) {
      this_player()->do_unwield(obj);
      this_player()->targetted_action(obj->query_unwield_message(), nil, obj);
   }

   if (obj->move(this_environment())) {
      this_player()->targetted_action("$N $vdrop $o.", nil, obj);
   } else {
      this_player()->targetted_action("$N $vtry to drop $o, but $vfail.", nil,
	 obj);
   }
}
