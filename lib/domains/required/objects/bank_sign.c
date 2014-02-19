inherit "/std/sign";
inherit "/std/modules/m_bank_teller";

void setup(void) {
   bank_init();
   set_message("The following commands are available at the bank:\n" +
      "\tbalance    : Get your balance.\n" +
      "\tdeposit #  : Deposit # coins in the bank.\n" +
      "\twithdraw # : Withdraw # coins from the bank.\n");
}
