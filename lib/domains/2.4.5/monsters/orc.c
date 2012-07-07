inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;
#define DIR "/domains/2.4.5"

void setup() {
   object obj;
   set_name("orc");
   set_gender( "male" );
   add_adj("dirty");
   set_in_room_desc("An orc");
   set_long("A dirty smelly orc.");
   set_race("orc");
   set_aggressive(1);
   set_level(random(2) + 1);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   is_blocking("north");

   switch(random(3)) {
      case 0:
         obj = clone_object(DIR + "/obj/knife.c");
      case 1:
         obj = clone_object(DIR + "/obj/curved_knife.c");
      default:
         obj = clone_object(DIR + "/obj/axe.c");
   }
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}

// XXX need to do chats...
