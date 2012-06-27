inherit CONTAINER;
#define DIR "/domains/newbie"

void setup(void) {
   set_id("table");
   set_adj("wooden", "small");
   set_long("A small wooden end table.");
   set_objects(([
      DIR + "/obj/potion":1,
   ]));
}
