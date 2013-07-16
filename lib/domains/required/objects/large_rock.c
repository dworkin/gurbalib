inherit "/std/object";

void setup(void) {
   set_id("rock");
   set_adj("large");
   set_short("A large rock");
   set_long("A pretty boring grey rock.");
   set_gettable(1);
   set_weight(10);
   /* This isn't a special rock... */
   set_value(0);
}
