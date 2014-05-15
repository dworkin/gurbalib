inherit "/std/shield";

void setup(void) {
   add_ids("tower shield");
   set_adj("large");
   set_short("A large tower shield");
   set_long("A large tower shield It has an intricate holy symbol " +
      "elaborately created on the front of the tower shield. It is " +
      "heavy and sturdy.");
   set_gettable(1);

   set_ac(4);

   set_wield_type("single");
   set_wield_message("$N $vtake up $p $o.");
   set_unwield_message("$N $vremove $p $o.");
   set_value(1000);
   set_size(35);
   set_weight(3);
   add_bane("holy");
}
