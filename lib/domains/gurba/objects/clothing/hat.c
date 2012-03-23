inherit ARMOR;

void setup(void) {
   set_id("sombrero", "hat");
   set_adj("large", "huge");
   set_long("Your average sombrero.");
   set_in_room_desc("A huge sombrero.");
   set_gettable(1);
   set_slot("head");
   set_wear_message("$N $vput $o on $p head.");
   set_remove_message("$N $vtake off $o.");
}
