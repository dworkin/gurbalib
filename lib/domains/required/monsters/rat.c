inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("rat");
   /* Leave out the gender specification, get a random one */
   /*  set_gender( "male" ); */
   add_adj("filthy");
   set_in_room_desc("A small filthy rat.");
   set_long("The rat smells awful.");
   set_race("rodent");
   set_max_hp(7);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}
