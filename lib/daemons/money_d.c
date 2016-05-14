/* Created 23/2-98 by Fudge */

mixed *currencies;

void create(void) {
   currencies = ({
      ({ "ducat", 1 }),    /* The base coin */
      ({ "royal", 10 }),   /* royal = 10 ducat's */
      ({ "crown", 100 })
   });
}

int is_currency(string coin) {
   int i;

   for (i = 0; i < sizeof(currencies); i++) {
      if (currencies[i][0] == lowercase(coin)) {
         return 1;
      }
   }
   return 0;
}

int query_value(string coin) {
   int i;

   for (i = 0; i < sizeof(currencies); i++) {
      if (currencies[i][0] == lowercase(coin)) {
         return currencies[i][1];
      }
   }
   return 0;
}

string *query_currencies(void) {
   int i;
   string *cur;

   cur = ( {  } ); 
   for (i = 0; i < sizeof(currencies); i++) {
      cur += ( { currencies[i][0] } );
   }
   return cur;
}
