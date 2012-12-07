inherit ARMOR;

void setup(void) {
   set_id("gloves");
   set_adj("red");
   set_long("A pair of leather gloves.");
   set_in_room_desc("A pair of gloves.");
   set_gettable(1);
   set_slot("hands");
   set_wear_message("$N $vwear $o.");
   set_remove_message("$N $vremove $o.");
   set_value(20);
   set_weight(5);
}
