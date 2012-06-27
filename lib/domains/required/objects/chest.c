inherit CONTAINER;
inherit M_OPENABLE;
#define DIR "/domains/required"

void setup(void) {
   set_id("chest");
   set_adj("wooden", "big");
   set_long("A big wooden chest.");
   set_open_state(0);

   set_objects(([
      DIR + "/objects/small_rock" : 1, 
      DIR + "/objects/large_rock" : 1,
   ]));

}
