inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("guard");
   set_gender( "female" );
   // set_level(11);
   set_in_room_desc("A guard");
   set_long("A big and sturdy guard.");
   set_race("human");
   set_max_hp(200);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   // XXX add_item("/domains/2.4.5/obj/bankkey.c",1);
   // add_item("/domains/2.4.5/obj/shortsword.c",1);
}
