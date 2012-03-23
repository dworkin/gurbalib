void usage() {
   write("Usage: close [-h] [all|OBJ]\n");
   write("Allows you to close a given object OBJ.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\tall\tClose all available items.\n");
}

string *query_verb_info() {
   return (( { "", "OBJ", "OBJA" }));
}

int can_close() {
   return 1;
}

int can_close_str(string str) {
   return 1;
}

int can_close_obj(object obj) {
   return 1;
}

void do_close() {
   write("Close what?");
}

void do_close_str(string str) {
   object *inv;

   int i;

   if (lowercase(str) != "all" && lowercase(str) != "everything"
      && lowercase(str) != "all doors" && lowercase(str) != "every door") {
      write("You can't seem to find the " + str + ".");
      return;
   }

   if (lowercase(str) == "all" || lowercase(str) == "everything") {
      inv = this_environment()->query_inventory();
      for (i = 0; i < sizeof(inv); i++) {
	 if (inv[i]->is_closable()) {
	    inv[i]->do_close(this_player());
	 }
      }
   } else if (lowercase(str) == "all doors" || lowercase(str) == "every door") {
      inv = this_environment()->query_inventory();
      for (i = 0; i < sizeof(inv); i++) {
	 if (inv[i]->is_closable() && inv[i]->is_door()) {
	    inv[i]->do_close(this_player());
	 }
      }
   }
}

void do_close_obj(object obj) {
   if (!obj->is_closable()) {
      write("You can't close the " + obj->query_id() + ".");
   }
   obj->do_close(this_player());
}
