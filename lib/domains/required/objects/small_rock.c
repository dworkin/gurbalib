inherit "/std/object";

void setup(void) {
   set_id("rock");
   set_adj("small");
   set_short("A small rock");
   set_long("A pretty boring grey rock.");
   set_gettable(1);
   set_weight(1);
   /* This isn't a special rock... */
   set_value(0);
}
