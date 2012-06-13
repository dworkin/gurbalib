inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("frog");
   /* Leave out the gender specification, get a random one */
   /*  set_gender( "male" ); */
   add_adj("cute");
   set_in_room_desc("A cute little frog");
   set_long("The grey wolf, running around.  It has some big dangerous teeth.");
   set_race("frog");
   set_max_hp(100);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

// Needs work still and a crown?  plane9

