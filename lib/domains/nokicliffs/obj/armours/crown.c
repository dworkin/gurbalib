inherit "/std/armor";

void setup(void) {
   set_id("crown");
   set_adj("metal");
   set_short("A metal crown");
   set_long("This crown functions as a useful helmet." +
      " It is a simple crown of metal but you know that it's ancient " +
      "and has rested upon the heads of champions throughout the " +
      "ages.");
   set_gettable(1);
   set_slot("head");
   set_wear_message("$N $vdon $o.");
   set_remove_message("$N $vtake off $o");
   set_ac(2);
   set_value(3000);
   set_size(3);
   set_weight(1);
}
