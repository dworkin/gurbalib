inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;
#define INTERVAL 5
int count;

void setup() {
   object obj;

   set_name("wyrm");
   set_short("The wyrm of Arcanarton");
   set_long("The giant undead dragon wyou see before you is the result " +
       "of one of Arcanarton's magic experiments..");
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 100);
   set_skill("combat/defense", 100);
   set_level(17);
   set_aggressive(1);

   obj = clone_object(DIR + "/obj/jem");
   obj->setup();
   obj->move(this_object());

   obj = clone_object("/domains/required/objects/coin.c");
   obj->set_amount(random(500) + 1);
   obj->move(this_object());
   obj->setup();
}

void do_extra_actions() {
   count = count + 1;
   if (count >= INTERVAL) {
/* XXX Do breathe death on you */
      count = 0;
   }
}
