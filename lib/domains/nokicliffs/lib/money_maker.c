#include "../domain.h"

static object make_money(string type, int amt) {
   object coins;

   coins = clone_object("/domains/required/objects/coin.c");
   coins->set_currency(type);
   coins->set_amount(amt);

   return coins;
}