inherit "/std/container";
inherit "/std/modules/m_openable";
#define DIR "/domains/required"

void setup(void) {
   set_id("chest");
   set_adj("wooden", "big");
   set_short("A big wooden chest");
   set_long("This thing looks like it weights a ton.  It's massive.");
   set_open_state(0);
   set_internal_max_weight(3000);

   set_objects(
      DIR + "/objects/small_rock", 
      DIR + "/objects/large_rock"
   );
}
