#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_block_exits";

void setup() {
   set_name("dwarf");
   set_gender( "male" );
   add_adj("sturdy");
   set_short("A sturdy looking dwarf");
   set_long("The dwarf is small, but built like a pile of bricks.");
   set_race("dwarf");
   set_aggressive(1);
   set_level(10);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   add_block("north");
}

int do_block(object who) {
   return 1;
}
