#include "../domain.h"

inherit DIR + "/lib/fibo";
inherit DIR + "/lib/vendor";

static int count;

void setup(void) {
   set_name("bootlegger");
   set_gender("female");
   set_short("Bootlegger");
   set_long("Bootlegger is a young woman who is known for " +
      "buying just about anything that can be bought.");
   set_race("human");
   set_level(5);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", NOKICLIFFS_OFFENSE);
   set_skill("combat/defense", NOKICLIFFS_DEFENSE);
   count = 0;
}

private void say_current_lucky_numbers(void) {
   int m, n;
   string fibos_string;
   float *fibos;
   fibos_string = "";

   m = random(10) + 1;
   n = m + random(10) + 1;
   fibos = get_m_through_n_fibonacci(m, n);
   for (m = 0; m < sizeof(fibos); m++) {
      fibos_string = fibos_string + ("" + fibos[m]);
      if (m < sizeof(fibos) - 1) {
        fibos_string += ", ";
      }
   }
   respond("say Current lucky numbers are " + fibos_string);
}

void do_extra_actions(void) {
   count = count + 1;
   if (count >= 30) {
      if (random(1) == 0) {
         say_current_lucky_numbers();
      }
      count = 0;
   }
}

void outside_message(string str) {
   string who, what;
   object player;

   str = ANSI_D->strip_colors(str);
   str = lowercase(str);

   if (sscanf(str, "%s gives %s to you.", who, what) == 2) {
      player = this_environment()->present(who);
      respond("say Thanks, " + player->query_Name() + ", but I " +
         "probably would have bought it.");
   }
}
