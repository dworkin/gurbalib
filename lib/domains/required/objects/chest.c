inherit CONTAINER;
inherit M_OPENABLE;
#define DIR "/domains/required"

void setup(void) {
   set_id("chest");
   set_adj("wooden", "big");
   set_short("A big wooden chest");
   set_long("This thing looks like it weights a ton.  It's massive.");
   set_open_state(0);

   set_objects(([
      DIR + "/objects/small_rock" : 1, 
      DIR + "/objects/large_rock" : 1,
   ]));

}
