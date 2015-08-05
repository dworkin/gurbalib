inherit "/std/armor";

void setup(void) {
   set_id("robe");
   set_short("A monk's robe");
   set_long("The monk's robe is constructed of simple materials. It is " +
      "sturdy enough but one ought " +
      "not to rely upon it for protection from " +
      "blows. The monk's robes were almost certainly fabricated by the " +
      "monk who originally owned it.");
   set_gettable(1);
   set_slot("body");
   set_wear_message("$N $vput on $o, and $vlook like a monk.");
   set_remove_message("$N $vtake off $o, and no longer $vlook like a monk.");
   set_ac(2);
   set_value(5);
   set_size(4);
   set_weight(2);
}
