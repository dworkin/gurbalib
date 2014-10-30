inherit "/std/monster";

void setup(void) {
   set_name("spider");
   /* Leave out the gender specification, get a random one */
   /*  set_gender( "male" ); */
   add_adj("large");
   set_short("A large spider");
   set_long("You thought the small ones were creepy.  This one is at least" +
      "two feet across, and it looks like it thinks your a snack.");

   set_race("spider");
   set_level(1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   set_aggressive(1);
}
