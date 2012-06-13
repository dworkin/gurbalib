inherit ARMOR;

void setup(void) {
   set_id("armour");
   set_adj("leather");
   set_long("A soft leather armour");
   set_gettable(1);
   set_slot("body");
   set_wear_message("$N $vput on $o.");
   set_remove_message("$N $vtake off $o.");
   set_ac(3);
   set_value(110);
   // XXX set_weight(3);
}
