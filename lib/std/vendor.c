inherit "/std/monster";
inherit "/std/modules/m_messages";
inherit "/std/modules/m_triggers";

static mapping stored_items;
static int will_buy, will_sell, restock_delay;

void init_stored_items(void) {
   if (!stored_items) {
      stored_items = ([ ]);
   }
}

string ducats(int val) {
   return val == 1 ? "" : "s";
}

int is_vendor(void) {
   return 1;
}

void set_restock_delay(int delay) {
   restock_delay = delay;
   call_out("restock", delay);
}

void restock(void) {
   this_object()->setup();
}

void set_will_buy(int will) {
   will_buy = will;
}

int query_will_buy(void) {
   return will_buy;
}

void set_will_sell(int will) {
   will_sell = will;
}

int query_will_sell(void) {
   return will_sell;
}

void do_sell(object player, string what) {
   string *objs;
   object obj;
   int i, found, value, maxi;

   init_stored_items();
   objs = map_indices(stored_items);

   found = 0;
   maxi = sizeof(objs);
   for (i = 0; i < maxi; i++) {

      obj = clone_object(objs[i]);
      if (obj) {
         obj->move(this_object());
         obj->setup();

         /* Found the object */
         if (obj->query_id() == what && found != 1) {
            value = obj->query_value();

            if (stored_items[objs[i]] < 1) {
               /* Skip here, out of stock... */
            } else {
               if (value <= player->query_total_money() ) {
                  this_object()->other_action(this_object(),
                     "$N $vgive $t $o", player, obj);
                  value = -1 * value;
                  player->add_money("ducat", value);
                  obj->move(player);
                  stored_items[objs[i]] = stored_items[objs[i]] - 1;
                  found = 1;
                  return;
               } else {
                  write("You do not have enough money for that.\n");
                  obj->query_environment()->remove_object(obj);
                  obj->destruct();
                  return;
               }
            }
         } else {
            obj->query_environment()->remove_object(obj);
            obj->destruct();
         }
      }
   }

   if (found == 0) {
      player->message("That item is out of stock.");
   }
}

void do_buy(object player, object what) {
   string name;
   int value;

   value = what->query_value();

   if ((will_buy < 1) || (value < 1)) {
      write(capitalize(this_object()->query_name()) + " will not buy that.\n");
      return;
   }

   name = what->base_name();

   if (!what->move(this_object())) {
      write("You can not sell that.\n");
      return;
   }

   player->targeted_action("$N $vsell $t $o for " + value + " ducat" +
      ducats(value) + ".",
      this_object(), what);
   what->query_environment()->remove_object(what);
   what->destruct();

   init_stored_items();
   if (!member_map(name, stored_items)) {
      stored_items[name] = 1;
   } else {
      stored_items[name] = stored_items[name] + 1;
   }

   player->add_money("ducat", value);
}

void add_item(string name, int amount) {

   if (amount == 0) {
      amount = 1;
   }

   init_stored_items();
   stored_items[name] = amount;
}

string build_string(string str, object obj, string num, string *objs) {
   int val;

   val = obj->query_value();
   if (!obj->query_Name()) {
      if (!obj->query_adj() || obj->query_adj() == "") {
         str += " %^CYAN%^[" + num + "]%^RESET%^ " + obj->query_id() +
            ", " + val + " ducat" + ducats(val) + ".\n";
      } else {
         str += " %^CYAN%^[" + num + "]%^RESET%^ " +
            obj->query_adj() + " " + obj->query_id() + ", " +
            val + " ducat" + ducats(val) + ".\n";
      }
   } else {
      val = objs->query_value();
      str += " %^CYAN%^[" + num + "]%^RESET%^ " + obj->query_Name() +
         ", " + val + " ducat" + ducats(val) + ".\n";
   }

   return str;
}

string query_list(void) {
   string str, num, *objs;
   object obj;
   int i, maxi;

   init_stored_items();
   objs = map_indices(stored_items);
   str = "";

   maxi = sizeof(objs);
   for (i = 0; i < maxi; i++) {

      if (stored_items[objs[i]] > 0) {
         obj = clone_object(objs[i]);
         if (obj) {

            obj->move(this_object());
            obj->setup();

            num = "   " + stored_items[objs[i]];
            num = num[strlen(num) - 3..];

            str = build_string(str, obj, num, objs);

            obj->query_environment()->remove_object(obj);
            obj->destruct();
         }
      }
   }
   return str;
}

void do_list(object player) {
   write("%^BLUE%^=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" +
      "-=-=-=-=-=-=-=-=-=-=-=-%^RESET%^\n\n");
   write(query_list());
   write("%^BLUE%^\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" +
      "-=-=-=-=-=-=-=-=-=-=-=-=-%^RESET%^\n");
}
