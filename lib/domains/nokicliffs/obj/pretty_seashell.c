inherit "/std/object";

void setup(void) {
   set_id("seashell");
   set_adj("pretty");
   set_short("A pretty seashell");
   set_long("A pretty seashell. You are aware of an ancient legend that " +
      "the Noki Cliffs guru has a fascination with seashells and sometimes " +
      "pays handsome rewards to those who give him one. He is, after all, " +
      "upon the summit of the highest cliffs around, where else is he " +
      "going to get seashells?");
   set_gettable(1);
   set_weight(1);
   set_value(1);
}
