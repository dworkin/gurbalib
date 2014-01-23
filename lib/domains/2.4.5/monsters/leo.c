#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

#define INTERVAL 8
int count;

void setup() {
   set_name("leo");
   set_gender( "male" );
   set_short("Leo the Archwizard");
   set_long("Leo the Archwizard.");
   set_race("human");
   set_level(40);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 90);
   set_skill("combat/defense", 200);

   set_spell_chance(50);
   set_spell_damage(30);
   set_spell_message("Leo casts a blazing fireball at $t.\n");
}

void do_extra_actions() {
   count = count + 1;
   if (count >= INTERVAL) {
      respond("smile");
      count = 0;
   }
}

/* XXX needs work */
void outside_message(string str) {
   string who, what;
   object sword, player;

   str = ANSI_D->strip_colors(str);
   str = str[..(strlen(str) - 3)];

   if (sscanf(str, "%s gives %s to you.", who, what) == 2) {
       player = this_environment()->present(who);
       sword = this_object()->present("orc slayer");

       if (sword) {
          destruct_object(sword);
          if (player->is_completed_quest("Orc Slayer")) {
          } else {
             player->add_completed_quest("Orc Slayer");
             player->increase_expr(200);
             player->message("Congratulations!!! You have just completed the " +
                "Orc Slayer quest.\n");
          }
       }
   } else if (sscanf(str, "%s says: %s",who,what) == 2) {
      what=lowercase(what);
      if (strstr(what[0..3], "hello") == 0 || 
          strstr(what[0..1], "hi") == 0) {
          player = this_environment()->present(who);

          this_object()->respond("say Welcome " + who + ".");
          if (player->query_level() >= 20) {
             this_object()->respond("say Now that you are a wizard " +
                who + ", you can have a castle of your own.\n");
   /* XXX Give user a castle if they ask for one.... */
          }
      }
   }
}
