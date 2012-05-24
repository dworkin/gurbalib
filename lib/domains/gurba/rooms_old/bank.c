inherit ROOM;

void setup(void) {
   set_brief("First National Bank of Gurba");
   set_long("This is the proud bank of Gurba. Two heavily armed guards " +
      "are standing on each side of the entrance. there are two counters " +
      "with a clerk behind each. One sign above the counter says " +
      "'Withdraw', the other says 'Deposit'. The floor and columns " +
      "supporting the roof are made of marble. This place reeks of " +
      "money. A huge sign hangs from the roof just after entering.");
   set_exits(([
      "south" : "/domains/gurba/rooms/market3",
   ]));

   add_item("counter", "counters",
      "Each of the counters is made out of solid oak.");
   add_item("guards", "guard", "The guards are dressed in full platemail, " +
      "with full helmets on top. They both have two-handed swords on " +
      "their backs and seem almost lifeless, statuelike standing there.");
   add_item("sign",
      "The sign exclaims in capital letters 'Robbery is not allowed'.");
   add_item("floor", "columns", "column", "The are nicely cut and tiled " +
      "out of marble. It is obvious that this is a place of money.");
   set_objects(([]));

}

void do_listen(object player) {
   write("You can even hear the sound of money.");
}
