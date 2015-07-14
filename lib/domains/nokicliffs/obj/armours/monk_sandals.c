inherit "/std/armor";

void setup(void) {
   set_id("sandals");
   set_short("A pair of monk's sandals");
   set_long("A pair of monk's boots. " +
      "These are made of very simple materials and skill. " +
      "They were probably made by the monk who was wearing " +
      "them upon the time of his demise. " +
      "However did you come by a pair of these?");
   set_gettable(1);
   set_slot("feet");
   set_wear_message("$N $vwear $o.");
   set_remove_message("$N $vremove $o.");
   set_value(2);
   set_size(4);
   set_weight(1);
}
