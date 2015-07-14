inherit "/std/armor";

void setup(void) {
   set_id("helmet");
   set_short("A helmet");
   set_long("A helmet. This is very basic advenuterer's gear. " +
      "You better find something else.");
   set_gettable(1);

   set_ac(1);

   set_slot("head");
   set_value(20);
   set_size(2);
   set_weight(1);
}
