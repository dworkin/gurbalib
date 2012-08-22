inherit obj OBJECT;
inherit light M_LIGHT;

void create(void) {
   light::create();
   obj::create();
}

void setup(void) {
   set_id("torch");
   set_adj("large");
   set_long("A stick with some burnable stuff stuck to the end of it.");
   set_in_room_desc("A torch");
   set_gettable(1);

   set_value(1);
   set_weight(10);
   set_fuel(1000);
}

/* XXX Need to add functions to light it and extinquish it??? 
   Should it be here or in the M_LIGHT code????
*/
