inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;

void setup() {
   set_name("beggar");
   set_gender( "male" );
   set_in_room_desc("A beggar");
   set_long("A really filthy looking poor beggar.");
   set_race("human");
   set_max_hp(30);
   set_level(3);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   //add_chat("Beggar says: Please, give money to a poor beggar!");
   //add_chat("Beggar says: Why can't I find any money?");
   //add_chat("Beggar says: two coins please.");
   //if talked to
   // add_chat("Beggar says: Why do you do this to me?");
}

// XXX  if given money and has > 12 coins go by beer  
// call_other(begger, "go east");
// call_other("buy beer");
// call_other("drink beer");
// call_other("west");

