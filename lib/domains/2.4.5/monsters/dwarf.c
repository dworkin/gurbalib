inherit MONSTER;
inherit M_BLOCKEXITS;

void setup() {
   set_name("dwarf");
   set_gender( "male" );
   add_adj("sturdy");
   set_in_room_desc("A sturdy looking dwarf");
   set_long("The dwarf is small, but built like a pile of bricks.");
   set_race("dwarf");
   // XXX set_level(10);
   // XXX set_aggressive(1);
   set_max_hp(100);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   is_blocking("north");
}

