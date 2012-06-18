inherit OBJECT;

void setup(void) {
   set_id("torch");
   set_adj("large");
   set_long("A stick with some burnable stuff stuck to the end of it.");
   set_in_room_desc("A torch");
   set_gettable(1);

   set_value(1);
   // XXX set_weight(10);
   // XXX Also need to make it lightable????
}
