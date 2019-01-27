inherit "/std/armor";

void setup(void) {
   set_id("rubber boots");
   set_adj("rubber");
   add_id("boots");
   set_short("A pair of rubber boots");
   set_long("The rubber boots are useful for keeping your feet dry when walking through water.");
   set_gettable(1);

   set_ac(1);

   set_slot("feet");
   set_value(20);
   set_size(2);
   set_weight(1);
}
