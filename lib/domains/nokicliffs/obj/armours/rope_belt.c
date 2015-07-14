inherit "/std/armor";

void setup(void) {
   set_id("belt", "rope belt");
   add_adj("simple");
   set_short("A simple rope belt");
   set_long("This is a simple rope belt. It can be used only as a belt.");
   set_gettable(1);
   set_slot("waist");
   set_wear_message("$N $vtie $o.");
   set_remove_message("$N $vuntie $o.");
   set_ac(1);
   set_value(2);
   set_size(6);
   set_weight(1);
}
