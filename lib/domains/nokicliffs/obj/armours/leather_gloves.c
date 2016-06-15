inherit "/std/armor";

void setup(void) {
   set_id("gloves");
   set_adj("leather");
   set_short("A pair of leather gloves");
   set_long("A standard pair of adventurer's leather gloves.");
   set_gettable(1);
   set_slot("hands");
   set_wear_message("$N $vwear $o.");
   set_remove_message("$N $vremove $o.");
   set_value(20);
   set_size(3);
   set_weight(1);
   set_ac(2);
}

void after_wear(object player) {
   player->message("Slipping on the gloves makes you " +
      "feel like you are ready for some adventure.");
}
