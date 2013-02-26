#include <mudlib.h>
inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;

void setup() {
   set_name("kitten");
   set_gender("male");
   set_short("An ADORABLE little kitten");
   set_long
      ("This little ball of fuzz is the cutest thing you've EVER seen.  When you look at it it cocks it head in curiousity and emits a small mewing noise... AWW!");
   set_max_hp(3000);
   set_hp(3000);
   set_damage_bonus(1300);
   set_hit_skill("combat/unarmed");
   set_actions(30, ( { "dervish", "purr" } ) );
   add_pattern("%s pets you.", "say yo wassup?");
   add_pattern("%s kicks you.", "say I'll kick your f**king ass!");
}
