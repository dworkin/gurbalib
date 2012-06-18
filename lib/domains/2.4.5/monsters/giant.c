inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("giant");
   // XXX set_level(15):
   set_in_room_desc("A giant");
   // XXX set_aggressive(1);
   set_long("A massive giant.");
   set_race("giant");
   set_max_hp(300);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

