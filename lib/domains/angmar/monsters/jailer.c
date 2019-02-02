#include "../domain.h"

inherit "/std/monster";

void setup(void) {
   set_name("jailer");
   set_gender("male");
   set_race("human");
   set_short("The jailer");
   set_long("He guards the dungeons.");
   add_money("ducat", 100 + random(50));
   set_level(20);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", BASE_OFFENSE * 4);
   set_skill("combat/defense", BASE_DEFENSE * 5);
}
