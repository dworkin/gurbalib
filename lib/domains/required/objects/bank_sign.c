inherit SIGN;

void setup(void) {
   set_message("The following commands are available at the bank:\n" +
      "\tbalance    : Get your balance.\n" +
      "\tdeposit #  : Deposit # coins in the bank.\n" +
      "\twithdraw # : Withdraw # coins from the bank.\n");
   add_object_command("balance","do_balance");
   add_object_command("withdraw","do_withdraw");
   add_object_command("deposit","do_deposit");
   add_object_command("loan","do_loan");
}

/* XXX Fix it so object commands work when the object is in the room with you 
   as well as when you have the object... */

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
