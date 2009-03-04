/*
   Coded by: Satch
   File    : /std/body/coins.c
   Date    : 02.22.98

   Mon Feb 23 13:00:10 CET 1998 - Fudge added query_all_coins();
                                - Fudge added interface to MONEY_D

*/

mapping coins;

int      query_coin_type( string type ); /* Query a certain coin */
void      add_coins( string type, int amount ); /* add coins to player */
mixed   * query_all_coins(); /* get a list of all coins */


void create()
{
}

mixed *query_all_coins( void ) {
  mixed *c;
  string *ind;
  int i;

  if( !coins )
    return ({ });

  ind = map_indices( coins );
  c = ({ });
  for( i=0; i < sizeof( ind ); i++ ) {
    c+= ({ ({ ind[i], coins[ind[i]] }) });
  }
  return( c );
}

int query_coin_type( string type )
{
   if( !coins )
      return 0;

   if( !coins[type] )
      return 0;

   return coins[type];
}

void add_coins( string type, int amount )
{
   if( !coins )
      coins = ([ ]);

   if( !coins || !amount )
      return;

   if( !MONEY_D->is_currency( type ) )
     return;

   if( !coins[type] )
      coins[type] = amount;
   else
   coins[type] += amount;

   if( coins[type] < 1 )
      coins[type] = 0;
}










