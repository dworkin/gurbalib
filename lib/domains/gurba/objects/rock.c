inherit OBJECT;
inherit M_GETTABLE;

void setup(void) {
   set_id("rock");
   set_adj("grey");
   set_long("A pretty boooooring grey rock.");
   set_in_room_desc("A rock is lying on the ground.");
   set_gettable(1);
   set_weight(5);
}
