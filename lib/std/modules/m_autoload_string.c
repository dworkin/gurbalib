string autoload_string;

string query_autoload_string(void) {
   return autoload_string;
}

void set_autoload_string(string str) {
   autoload_string = str;
}

void clone_autoload_objects(void) {
   string file, argument, rest, str;
   object ob;

   str = autoload_string;
   while (str && str != "*^!") {
      if (sscanf(str, "%s:%s^!%s", file, argument, rest) == 3) {
      } else if (sscanf(str, "%s:%s^!", file, argument) != 2) {
         write("Autoload string corrupt.\n");
         return;
      } else {
         rest = "";
      }
      str = rest;
      if (file_exists(file)) {
         ob = clone_object(file);
         if (ob) {
            ob->move(this_object()->query_environment());
            ob->setup();
            ob->move(this_object());
            if (argument == "wield") {
               this_player()->do_wield(ob);
            } else if (argument == "wear") {
               this_player()->do_wear(ob);
            }
         }
      }
   }
}

void compose_autoload_string(void) {
   object ob;
   string str, tmp, action;
   object *inv;
   int i, max;

   str = "";
   inv = this_object()->query_inventory();
   max = sizeof(inv);
   for (i = 0; i < max; i++) {
      tmp = inv[i]->query_autoload_filename();
      if (inv[i]->query_worn()) {
         action = "wear";
      } else if (inv[i]->query_wielded()) {
         action = "wield";
      } else {
         action = "none";
      }
      if (tmp && (tmp != "")) {
         str = str + tmp + ":" + action + "^!";
      }
   }
   /* terminate autoload string */
   str = str + "*^!";
   this_object()->set_autoload_string(str);
}
