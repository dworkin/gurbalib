int coins; /* Players money on them */
int bank; /* Players money in the bank */

void create() {
}

mixed *query_all_coins(void) {
   string *currencies;
   int value, i, num, worth;
   mixed *c;

   c = ({ });

   value = coins;

   currencies = MONEY_D->query_currencies();

   for (i = sizeof(currencies) -1; i >= 0; i--) {
      worth = MONEY_D->query_value(currencies[i]);
      if (value > 0) {
         num = value / worth;
         value = value - (num * worth);
      } else {
          num = 0;
      }
      c += ( { ( { currencies[i], num } ) } );
   }
   return c;
}

int clear_money() {
   coins = 0;
}

int add_money(string type, int amount) {
   int value;

   value = MONEY_D->query_value(type);

   value = value * amount;
   value = coins + value;
   if (value > 0) {
      coins = value;
      return 1;
   }
   return 0;
}

int query_total_money() {
   return coins;
}

int query_bank() {
   return bank;
}

int withdraw(int x) {
   if (bank >= x) {
      bank -= x;
      coins += x;
      return 1;
   }
   return 0;
}

int deposit(int x) {
   if (coins >= x) {
      coins -= x;
      bank += x;
      return 1;
   }
   return 0;
}
