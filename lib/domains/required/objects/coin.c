/* Created by Fudge */
inherit OBJECT;

string text;
int amount;
string currency;

int set_currency(string str) {
   if (MONEY_D->is_currency(str)) {
      currency = str;
      return 1;
   }
   return 0;
}

string query_currency() {
   if (!currency) return "ducat";
   return currency;
}

int query_amount() {
   return amount;
}

void set_amount(int amt) {
   amount = amt;
   if (amt == 1) {
      set_in_room_desc("One " + currency);
      set_long("A lonely " + currency + ".");
   } else if (amt < 10) {
      set_in_room_desc("A couple of " + currency + "s");
      set_long("A couple of " + currency + "s.");
   } else if (amt < 20) {
      set_in_room_desc("A few " + currency + "s");
      set_long("A few " + currency + "s. About 15.");
   } else if (amt < 40) {
      set_in_room_desc("Some " + currency + "s");
      set_long("Some " + currency + "s. About 30.");
   } else if (amt < 80) {
      set_in_room_desc("Many " + currency + "s");
      set_long("Many " + currency + "s. About 50.");
   } else if (amt < 150) {
      set_in_room_desc("Lots of " + currency + "s");
      set_long("Lots of " + currency + "s. About 100.");
   } else {
      set_in_room_desc("A huge pile of " + currency + "s");
      set_long("A huge pile of " + currency +
	 "s. More than you'd care to count.");
   }
}

/* Setup some reasonable defaults.... */
void create(void) {
   ::create();
   set_currency("ducat");
   set_amount(1);

   set_id("coin");
   add_id("coins");
   set_long("A coin.");
   set_in_room_desc("A coin.");
   set_gettable(1);
   set_value(1);
}

int query_weight() {
   return 1;
}

int query_value() {
   int x;

   x = ::query_value();
   x *= amount;
   return x;
}

int is_money() {
   return 1;
}
