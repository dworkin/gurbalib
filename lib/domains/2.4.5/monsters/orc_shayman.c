inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   object obj;

   set_name("shayman");
   set_gender( "female" );
   add_adj("orc");
   set_in_room_desc("Orc shayman");
   set_long("An ugly orc shayman.  This thing looks wilder than your average " +
      "orc.");
   set_race("orc");
   set_max_hp(300);
   // XXX set_level(10);
   // XXX set_addressive(1);
   // XXX add magic missle spell...
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);

   obj = clone_object("/domains/2.4.5/obj/gold_staff.c");
   obj->setup();
   obj->move(this_object());
   obj = clone_object("/domains/2.4.5/obj/orc_slayer.c");
   obj->setup();
   obj->move(this_object());
   do_wield(obj);
}
