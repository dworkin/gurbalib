#include "../domain.h"

inherit "/std/monster";

void setup() {
   set_name("elf king");
   add_ids("king of the elves", "elf", "king");
   set_short("The elf king");
   set_long("This is the King of the Elves. Though small in stature, he " +
      "exudes a charisma and sense of capability that places you in awe. " +
      "He is mature, by elf standards, yet you get the feeling that he is " +
      "hundreds of years older than you are. He has a determined look on his face.");
   set_gender("male");
   set_race("elf");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   equip_monster(({
      DIR + "/obj/weapons/elf_sword.c"
   }));
}
