inherit obj "/std/object";
inherit light "/std/modules/m_light";

void create(void) {
   light::create();
   obj::create();
}

void setup(void) {
   set_id("torch");
   set_adj("large");
   set_long("A stick with some burnable stuff stuck to the end of it.");
   set_short("A torch");
   set_gettable(1);

   set_value(1);
   set_weight(10);
   set_fuel(1000);
}

/* XXX Need to add functions to light it and extinguish it??? 
   Should it be here or in the m_light code????
*/
