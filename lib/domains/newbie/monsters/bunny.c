inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("bunny");
   add_adj("fluffy");
   set_in_room_desc("A fluffy little bunny.");
   set_long("It doesn't look like much of a challenge.");
   set_race("rodent");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 20);
   set_skill("combat/defense", 20);
}
