inherit MONSTER;
inherit M_ACTIONS;
inherit M_TRIGGERS;
inherit M_BLOCKEXITS;
int count;
#define INTERVAL 5

void setup() {
   set_name("beggar");
   set_gender( "male" );
   set_short("A beggar");
   set_long("A really filthy looking poor beggar.");
   set_race("human");
   set_level(3);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

void do_extra_actions() {
   count = count + 1;

   if (count >= INTERVAL) {
      switch(random(3)) {
         case 0:
           respond("say Please, give money to a poor beggar!");
           break;
         case 1:
           respond("say Why can't I find any money?");
           break;
         default:
           respond("say Two coins please.");
           break;
      }
      count = 0;
   }
/* May need to change this up.... XXX check for coin and value? */
   if (this_object()->query_total_money() > 12) {
      respond("go east");
      respond("buy beer");
      respond("drink beer");
      respond("west");
   }
}

void outside_message(string str) {
   int x;
   str = ANSI_D->strip_colors(str);
   x = strlen(str) -3;
   
   str = str[..x];

   /* XXX need to fix this... if action on the beggar... */
   if (1) {
      respond("say Why do you do this to me?");
   }
}
