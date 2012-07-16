inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("leo");
   set_gender( "male" );
   set_in_room_desc("Leo the Archwizard");
   set_long("Leo the Archwizard.");
   set_race("human");
   set_level(40);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 90);
   set_skill("combat/defense", 200);
}

// XXX Need to setup chats
// XXX Need to do fireball spell as an attack option.
// XXX Quest for Orc slayer?
// XXX Give user a castle if they ask for one....

