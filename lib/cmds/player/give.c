inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: give [-h] [all|OBJ] [to] PLAYER" });
   lines += ({ "" });
   lines += ({ "Allows you to give OBJ to PLAYER" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tall\tGive everything you are carrying to PLAYER." });
   lines += ({ "Examples:" });
   lines += ({ "\tgive sword to sirdude" });
   lines += ({ "\tgive sword sirdude" });
   lines += ({ "\tgive all to sirdude" });
   lines += ({ "\tgive 5 ducats to sirdude" });
   lines += ({ "See also:" });
   lines += ({ "\tget, drop" });

   this_player()->more(lines);
}

static void do_give(object obj1, object obj2, int loud) {
   string slot;
   object worn;

   if (!obj1) {
      if (loud) {
         write("What are you trying to put where?");
      }
      return;
   }

   if (!obj2) {
      if (loud) {
         write("Where are you trying to put that?\n");
      }
      return;
   }

   if (!obj2->is_living()) {
      if (loud) {
         write("You can only give things to the living.\n");
      }
      return;
   }

   if (obj2 == this_player()) {
      if (loud) {
         write("You may not give things to yourself.\n");
      }
      return;
   }

   if (obj1->is_worn()) {
      if (obj1->is_cursed()) {
         this_player()->targeted_action("$N $vtry to remove $o, but $vfumble.",
            nil, obj1);
         write("Strange... It won't come off.\n");
         return;
      } else {
         this_player()->do_remove(obj1);
         this_player()->targeted_action(obj1->query_remove_message(), 
            nil, obj1);
			obj1->after_unwear(this_player(), "give");
      }
   }

   if (obj1->is_wielded()) {
      if (obj1->is_cursed()) {
         this_player()->targeted_action("$N $vtry to unwield $o, " +
            "but $vfumble.", nil, obj1);
         write("Strange... You can't unwield that..\n");
         return;
      } else {
         this_player()->do_unwield(obj1);
         this_player()->targeted_action(obj1->query_unwield_message(), 
            nil, obj1);
			obj1->after_unwield(this_player(), "give");
      }
   }

   if (obj1->move(obj2)) {
      this_player()->targeted_action("$N $vgive $o to $T.", obj2, obj1);
   } else {
      this_player()->targeted_action("$N $vtry to give $o to $T, but $vfail.",
         obj2, obj1);
   }
}

static int transfer_money(int amount,string cointype, string where) {
   object obj;
   int worth;

   obj = this_environment()->present(where);

   if (!obj) {
      write("Who are you trying to give that to?");
      return 0;
   }
   if (!obj->is_living()) {
      write("You can not give money to that.\n");
      return 0;
   }
   if (obj == this_player()) {
      write("You can not give yourself money.\n");
      return 0;
   }

   worth = MONEY_D->query_value(cointype);
   if (worth > 0) {
      amount = amount * worth;
      if (this_player()->query_total_money() > amount) {
         this_player()->add_money("ducat", (amount * -1));
         obj->add_money("ducat",amount);
			this_player()->targeted_action("$N $vgive " + amount +
				" ducats to $t.", obj);
         return 1;
      } else {
         write("You do not have enough money to give.\n");
         return 0;
      }
   } else {
      write("Error that is funny money.\n");
      return 0;
   }
   return 0;
}

static void main(string str) {
   object obj, obj2;
   object *inv;
   int i, max, amount;
   string what, where, coin;

   if (empty_str(str)) {
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

   if (sscanf(str, "%s to %s",what,where) == 2) {
      if (sscanf(what, "%d %s",amount, coin) == 2) {
         if ((coin == "ducat") || (coin == "ducats") || (coin == "coins")) {
            transfer_money(amount,"ducat",where);
            return;
         } else if ((coin == "royal") || (coin == "royals")) {
            transfer_money(amount,"royal",where);
            return;
         } else if ((coin == "crown") || (coin == "crowns")) {
            transfer_money(amount,"crown",where);
            return;
         }
      }
   } else if (sscanf(str, "%s %s",what,where) == 2) {
   } else {
      write("You want to give what to who?");
      return;
   }

   obj = this_environment()->present(where);
   if (!obj) {
      write("Who are you trying to give that to?");
      return;
   }

   if (what == "all") {
      inv = this_player()->query_inventory();
      max = sizeof(inv);
      for (i = 0; i < max; i++) {
         do_give(inv[i], obj, 0);
      }
      return;
   }

   obj2 = this_player()->present(lowercase(what));
   if (!obj2) {
      obj2 = this_player()->query_environment()->present(lowercase(what));
   }
   do_give(obj2, obj, 1);
}
