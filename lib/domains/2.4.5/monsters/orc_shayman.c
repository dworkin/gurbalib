#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

void setup() {
   object obj;

   set_name("shayman");
   set_gender( "female" );
   add_adj("orc");
   add_ids("orc", "orc shayman");
   set_short("Orc shayman");
   set_long("An ugly orc shayman.  This thing looks wilder than your average " +
      "orc.");
   set_race("orc");
   set_level(10);
   set_aggressive(1);

   set_spell_chance(20);
   set_spell_damage(20);
   set_spell_message("The shayman casts a magic missile at $t.");

   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object(DIR + "/obj/gold_staff.c");
   obj->setup();
   obj->move(this_object());
   obj = clone_object(DIR + "/obj/orc_slayer.c");
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}
