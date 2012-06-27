inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;
#define DIR "/domains/2.4.5"

void setup() {
   object obj;

   set_name("guard");
   set_gender( "female" );
   set_in_room_desc("A guard");
   set_long("A big and sturdy guard.");
   set_race("human");
   set_max_hp(200);
   set_level(11);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/bankkey.c");
   obj->setup();
   obj->move(this_object());
   obj = clone_object("/domains/required/objects/weapons/shortsword.c");
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}
