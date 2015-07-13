/* Created by Fudge */
inherit "/std/object";

string text, currency;
int amount;

int set_currency(string str) {
   if (MONEY_D->is_currency(str)) {
      currency = str;
      return 1;
   }
   return 0;
}

string query_currency(void) {
   if (!currency) {
      return "ducat";
   }
   return currency;
}

int query_amount(void) {
   return amount;
}

void set_amount(int amt) {
   amount = amt;
   if (amt == 1) {
      set_short("One " + currency);
      set_long("A lonely " + currency + ".");
   } else if (amt < 10) {
      set_short("A couple of " + currency + "s");
      set_long("A couple of " + currency + "s.");
   } else if (amt < 20) {
      set_short("A few " + currency + "s");
      set_long("A few " + currency + "s. About 15.");
   } else if (amt < 40) {
      set_short("Some " + currency + "s");
      set_long("Some " + currency + "s. About 30.");
   } else if (amt < 80) {
      set_short("Many " + currency + "s");
      set_long("Many " + currency + "s. About 50.");
   } else if (amt < 150) {
      set_short("Lots of " + currency + "s");
      set_long("Lots of " + currency + "s. About 100.");
   } else {
      set_short("A huge pile of " + currency + "s");
      set_long("A huge pile of " + currency +
         "s. More than you'd care to count.");
   }
}

int query_weight(void) {
   return 0;
}

int query_value(void) {
   int x;

   x = ::query_value();
   x *= amount;
   return x;
}

int is_money(void) {
   return 1;
}

/* Setup some reasonable defaults.... */
void create(void) {
   ::create();
   set_currency("ducat");
   set_amount(1);

   set_id("coin");
   add_id("coins");
   set_gettable(1);
   set_value(1);
}

