inherit CONTAINER;
inherit M_OPENABLE;

void setup(void) {
   set_id("chest");
   set_adj("wooden", "big");
   set_long("A big wooden chest.");
   set_open_state(0);

   set_objects(([
      "/domains/required/objects/small_rock" : 1, 
      "/domains/required/objects/large_rock" : 1,
   ]));

}
