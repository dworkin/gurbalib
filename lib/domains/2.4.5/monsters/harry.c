#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

#define INTERVAL 8
static int count;
string *a_str, *na_str;

void setup() {
   set_name("harry");
   add_id("fjant");
   set_gender("male");
   add_adj("affectionate");
   set_short("Harry the affectionate");
   set_long("Harry has an agreeable look.");
   set_race("human");
   set_level(3);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
   count = 0;

   a_str = ({
      "say Don't hit men",
      "say That hurt!",
      "say Help, someone!",
      "say Why can't you go bullying elsewhere?",
      "say Aooooo!",
      "say I hate bashers!\n",
      "say Bastard\n",
      "say You big brute!\n"            
   });

   na_str = ({
      "say What are you waiting for?",
      "say Hello there!",
      "say I don't like winter.",
      "say I don't like snow.",
      "say I don't like rain.",
      "say Who are you?",
      "say Why do you look like that?",
      "say What are you doing here?",
      "say Nice weather, isn't it?",
      "smile"
   });
}

void notify(string str) {
   query_environment()->tell_room(this_object(), str);
}

private int check_verb(string str, string verb) {
   return sscanf(str, verb + "%*s") == 1;
}

private int is_harry(string str) {
   return lowercase(str) == "harry";
}

/* XXX get harry from vill_road2.c  Needs lots of work... */
private void why_did(string str) {
   string who, what, tmp;

   sscanf(str, "%s %s", who, what);
   if (is_harry(who)) {
      return;
   }
   if (sscanf(what, "sells %*s") == 1) {
      respond("say Why did you sell " + what);
   }
   if (sscanf(str, "%s attacks %s.", who, what) == 2) {
      respond("say Why does " + who + " attack " + what + "?");
   }
   if (sscanf(str, "%s left the game.", who) == 1) {
      respond("say Why did " + who + " quit the game ?");
   }
   if (sscanf(str, "%s takes %s.\n", who, what) == 2) {
      respond("say Why did " + who + " take " + what + " ?");
   }
   if (sscanf(what, "drops %s.", tmp) == 1) {
      respond("say Why did " + who + " drop " + tmp + "?");
   }
}

private void how_does_it_feel(string str) {
   string who, what;
   sscanf(str, "%s %s", who, what);
   if (is_harry(who)) {
      return;
   }
   if (sscanf(str, "%s is now level %s.\n", who, what) == 2) {
      respond("say How does it feel, being of level " + what + " ?");
   }
}

private void smiles(string str) {
   string who, what;

   sscanf(str, "%s %s", who, what);
   if (is_harry(who)) {
      return;
   }
   if (check_verb(what, "smile") == 1) {
      respond("smile");
   }
}

private void say_hello(string str) {
   string who, what;

   sscanf(str, "%s %s", who, what);
   if (is_harry(who)) {
      return;
   }
   if (check_verb(what, "appears") == 1 || check_verb(what, "enters") == 1) {
      respond("say Hi " + who + ", nice to see you!");
   }
}

private int contains(string needle, string hay) {
   return sscanf(hay, "%*s" + needle + "%*s") == 2;
}

void handle_say(string str) {
   string a, b, message;

   sscanf(str, "%s %s", a, b);
   if (is_harry(a)) {
      return;
   }
   if (sscanf(str, "%s says: %s\n", a, b) != 2) {
      return;
   }

   str = lowercase(b);

   if (contains("hello", str) || contains("hi", str) ||
      contains("hello everybody", str)) {
      message = "say Pleased to meet you!";
   }
   if (contains("shut up", str)) {
      message = "say Why do you want me to shut up ?";
   }
   if (contains("stay here", str) || contains("not follow", str) ||
      contains("get lost", str)) {
      message = "say Ok then.";
   }
   if (!message) {
      message = "say Why do you say '" + str + "'???";
   }
   respond(message);
}

private void follow(string str) {
   string who, where;

   if (sscanf(str, "%s leaves %s.\n", who, where) == 2) {
      if (!is_harry(who)) {
         respond("go " + where);
      }
   }
}

private void gives(string str) {
   string who, what;
   int rand;
   object obj, next_obj, who_obj;

   if (sscanf(str, "%s gives the %s to you.", who, what) != 2) {
      return;
   }

   if ((what == "firebreather" || what == "special" ||
         what == "beer" || what == "bottle") && this_object()->present(what)) {
      rand = random(4);

      if (rand == 0) {
         if (random(10) > 6) {
            respond("sigh");
            respond("say I guess you're gonna kill me now.");
            respond("drop all");
            respond("go west");
         }
      }
      if (rand == 1) {
         respond("drink " + what);
      }
      if (rand == 2) {
         respond("drop " + what);
      }
      if (rand == 3) {
         obj = this_object()->present(what);
         if (obj) {
            respond("give " + what + " to " + who);
         }
      }
   } else if (what == "corpse") {
      respond("say HEY, bury your corpses yourself, asshole.");
      obj = this_object()->present(what);
      if (obj) {
         respond("give corpse to " + who);
      }
   } else {
      if (this_object()->present(what)) {
         who_obj = this_object()->query_environment()->present(who);
         /* XXX sir, ma'am, creature... */
         respond("say Thank you very much, sir.");
      }
   }
}

/* XXX implement this. */
void monster_died() {
}

int down() {
   call_other(this_player(), "move_player", DIR + "/rooms/station");
   return 1;
}

void do_extra_actions() {
   count++;

   if (count >= INTERVAL) {
      if (is_fighting()) {
         respond(a_str[random(sizeof(a_str))]);
      } else {
         respond(na_str[random(sizeof(na_str))]);
      }
      count = 0;
   }
}

void outside_message(string str) {
   /* XXX some from these can be spoofed with player emotes... */
   if (is_fighting()) {
      return;
   }

   str = ANSI_D->strip_colors(str);
   smiles(str);
   say_hello(str);
   why_did(str);
   follow(str);
   gives(str);
   handle_say(str);
}
