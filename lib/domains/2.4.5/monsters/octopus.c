inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("octopus");
   add_adj("giant");
   set_in_room_desc("An octopus");
   set_long("A very big octopus with long arms, reaching for you.");

   set_race("frog");
   set_level(10);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

// XXX Needs work still sea_bottom

