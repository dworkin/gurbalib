/* A standard set of banking commands that can be added to any object, room or
 * mobile.  You must call bank_init() in the create() or setup() functions of
 * the object inheriting this module */
 
 void add_object_command(string command, string func);
 
 void bank_init(void) {
   add_object_command("balance","do_balance");
   add_object_command("withdraw","do_withdraw");
   add_object_command("deposit","do_deposit");
   add_object_command("loan","do_loan");
 }
 
int do_balance(string str) {
   int amount;

   amount = this_player()->query_bank();
   write("Your current balance is: " + amount + " ducats.\n");
   return 1;
}

int do_withdraw(string str) {
   int amount;

   if (sscanf(str, "%d",amount)) {
      if (this_player()->withdraw(amount)) {
          write("You withdraw " + amount + " ducats from the bank.\n");
      } else {
          write("You do not have " + amount + " ducats in the bank.\n");
      }
      write("Your current balance is: " + amount + " ducats.\n");
      return 1;
   } else {
      write("Usage: withdraw (amount)\n");
      return 1;
   }
}

int do_deposit(string str) {
   int amount;

   if (sscanf(str, "%d",amount)) {
      if (this_player()->deposit(amount)) {
          write("You deposit " + amount + " ducats in the bank.\n");
      } else {
          write("You do not have " + amount + " ducats.\n");
      }
      write("Your current balance is: " + amount + " ducats.\n");
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
         this_player()->add_money(amount);
         write("The bank loans you " + amount + " ducats.\n");
         return 1;
      } else {
         write("Usage: loan (amount)\n");
         return 1;
      }
   } 
   return 0; 
}
