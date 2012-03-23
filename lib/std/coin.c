/* Created by Fudge */

inherit OBJECT;
inherit M_GETTABLE;

string text;
int amount;
string currency;

void create(void) {
   ::create();
   set_id("coin");
   if (amount > 1) {
      set_long("Some coins.");
      set_in_room_desc(amount + " coins.");
   } else {
      set_long("A coin.");
      set_in_room_desc("A coin.");
   }
   set_gettable(1);
}

void set_currency(string str) {
   currency = str;
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
