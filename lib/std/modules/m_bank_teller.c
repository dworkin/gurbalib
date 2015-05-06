/* A standard set of banking commands that can be added to any object, room or
 * mobile.  You must call bank_init() in the create() or setup() functions of
 * the object inheriting this module */
 
void add_action(string func, string command);
 
void bank_init(void) {
   add_action("do_balance", "balance");
   add_action("do_withdraw", "withdraw");
   add_action("do_deposit", "deposit");
   add_action("do_loan", "loan");
 }
 
int do_balance(varargs string str) {
   int amount;

   amount = this_player()->query_bank();
   write("Your current balance is: " + amount + " ducats.\n");
   return 1;
}

int do_withdraw(string str) {
   int amount;

   if (sscanf(str, "%d",amount)) {
      if (amount < 1) {
         write("Please enter a positive number.\n");
         return 1;
         }
      if (this_player()->withdraw(amount)) {
          write("You withdraw " + amount + " ducats from the bank.\n");
      } else {
          write("You do not have " + amount + " ducats in the bank.\n");
      }
      do_balance();
      return 1;
   } else {
      write("Usage: withdraw (amount)\n");
      return 1;
   }
}

int do_deposit(string str) {
   int amount;

   if (sscanf(str, "%d",amount)) {
      if (amount < 1) {
         write("Please enter a positive number.\n");
         return 1;
         }
      if (this_player()->deposit(amount)) {
          write("You deposit " + amount + " ducats in the bank.\n");
      } else {
          write("You do not have " + amount + " ducats.\n");
      }
      do_balance();
      return 1;
   } else {
      write("Usage: deposit (amount)\n");
      return 1;
   }
}

int do_loan(string str) {
   int amount;

   if (query_wizard(this_player())) {
      if (sscanf(str, "%d",amount)) {
         this_player()->add_money("ducat", amount);
         write("The bank loans you " + amount + " ducats.\n");
         return 1;
      } else {
         write("Usage: loan (amount)\n");
         return 1;
      }
   } 
   return 0; 
}
