inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: drop [-h] [all|OBJ]" });
   lines += ({ "" });
   lines += ({ "Allows you to drop a given object OBJ." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tDrop everything you are carrying." });
   lines += ({ "Examples:" });
   lines += ({ "\tdrop sword" });
   lines += ({ "\tdrop all" });
   lines += ({ "See also:" });
   lines += ({ "\tget, put, remove, wear, wield" });

   this_player()->more(lines);
}

static int do_drop_coin(int amount,string type) {
   object obj;

   if ((type == "ducat") || (type == "ducats") || (type == "coins")) {
      /* No need to change amount */
   } else if ((type == "royal") || (type == "royals")) {
      amount = amount * MONEY_D->query_value("royal");
   } else if ((type == "crown") || (type == "crowns")) {
      amount = amount * MONEY_D->query_value("crown");
   } else {
      return 0;
   }

   if (this_player()->query_total_money() > amount) {
      this_player()->add_money("ducat", (amount * -1));
      write("you drop " + amount + " ducats.");
      this_player()->query_environment()->tell_room(this_player(),
         this_player()->query_Name() + " drops " + amount + "ducats.\n");
      obj = clone_object(DOMAINS_DIR + "/required/objects/coin.c");
      obj->set_amount(amount);
      obj->move(this_player()->query_environment());
   } else {
      write("You do not have that much money.\n");
   }
   return 1;
}

static void do_drop(object obj, int loud) {
   string slot;
   object worn;

   if (!obj) {
      if (loud) {
         write("what are you trying to drop?");
      }
      return;
   }

   if (obj->is_undroppable()) {
      if (loud) {
         write("You cannot drop that.");
      }
      return;
   }
   if (obj->query_worn() == 1) {
      if (obj->is_cursed()) {
         if (loud) {
            this_player()->targetted_action("$N $vtry to remove $o, " +
               "but $vfumble.", nil, obj);
            write("Strange... It won't come off.\n");
         } 
         return;
      } 
      this_player()->do_remove(obj);
      this_player()->targetted_action(obj->query_remove_message(), nil, obj);
   }
   if (obj->query_wielded() == 1) {
      if (obj->is_cursed()) {
         if (loud) {
            this_player()->targetted_action("$N $vtry to remove $o, " +
               "but $vfumble.", nil, obj);
            write("Strange... It won't come off.\n");
         } 
         return;
      }
      this_player()->do_unwield(obj);
      this_player()->targetted_action(obj->query_unwield_message(), nil, obj);
   }

   if (obj->move(this_environment())) { 
      this_player()->targetted_action("$N $vdrop $o.", nil, obj);
      obj->post_drop();
   } else {
      this_player()->targetted_action("$N $vtry to drop $o, but $vfail.", 
         nil, obj);
   }
}

static void main(string str) {
   object obj;
   object *inv;
   int i, max, amount;
   string type;

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   if (str == "all") {
      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_drop(inv[i],0);
      }
      return;
   }

   if (sscanf(str, "%d %s", amount, type) == 2) {
      if (do_drop_coin(amount,type)) {
         return;
      }
   }

   obj = this_player()->present(lowercase(str));
   do_drop(obj,1);
}
