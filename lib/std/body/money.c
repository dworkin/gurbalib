int coins;

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
