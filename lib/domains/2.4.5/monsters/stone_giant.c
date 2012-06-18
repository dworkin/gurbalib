inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("troll");
   /* Leave out the gender specification, get a random one */
   /*  set_gender( "male" ); */
   add_adj("smelly");
   set_in_room_desc("A large smelly troll.");
   set_long("The troll looks like a messed up tree.");
   set_race("troll");
   set_max_hp(100);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

