inherit "/std/monster";
inherit "/std/modules/m_triggers";

#include "../domain.h"

void setup() {
   set_name("harry");
   add_id("fjant");
   set_gender( "male" );
   add_adj("affectionate");
   set_short("Harry the affectionate");
   set_long("Harry has an agreeable look.");
   set_race("human");
   set_level(3);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 50);
   set_skill("combat/defense", 100);
}

void notify(string str) {
    query_environment()->tell_room(this_object(), str);
}

/* XXX get harry from vill_road2.c  Needs lots of work... */
void why_did(string str) {
   string who, what;

   sscanf(str, "%s %s", who, what);
   if(who == "harry" || who == "Harry") return;
   if (sscanf(str, "%s sells %s.", who, what) == 2) {
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
   if (sscanf(str, "%s drops %s.\n", who, what) == 2) {
      respond("say Why did " + who + " drop " + what + " ?");
   }
}

void how_does_it_feel(string str) {
   string who, what;
   sscanf(str, "%s %s", who, what);
   if(who == "harry" || who == "Harry") return;
   if (sscanf(str, "%s is now level %s.\n", who, what) == 2) {
      respond("say How does it feel, being of level " + what + " ?");
   }
}

void smiles(string str) {
   string who, what;

   sscanf(str, "%s %s", who, what);
   if (who == "harry" || who == "Harry")
      return;
   if (sscanf(str, "%s smiles happily", who) == 1 &&
      who != "Harry") {
      respond("smile");
   }
}

void say_hello(string str) {
   string who;

   if (sscanf(str, "%s arrives.", who) == 1) {
      respond("say Hi " + who + ", nice to see you !");
   }
}

void test_say(string str) {
   string a, b, message;

   sscanf(str, "%s %s", a, b);
   if(a == "harry" || a == "Harry") return;
   if (!sscanf(str, "%s says: %s\n", a, b) == 2) return;

   str = b;

   if (str == "hello" || str == "hi" || str == "hello everybody") {
      message = "say Pleased to meet you!";
   }
   if (str == "shut up") {
      message = "say Why do you want me to shut up ?";
   }
   if (sscanf(str, "%sstay here%s", a, b) == 2 ||
      sscanf(str, "%snot follow%s", a, b) == 2 ||
      sscanf(str, "%sget lost%s", a, b) == 2) {

      message = "say Ok then.";
   }
   if(!message) message = "say Why do you say '" + str + "'???";
   respond(message);
}

void follow(string str) {
   string who, where;

   if(sscanf(str, "%s leaves %s.\n", who, where) == 2)
      call_other(this_object(), "init_command", where);
}

void gives(string str) {
   string who, what, whom;
   int rand;
   object obj, next_obj;

   if(sscanf(str, "%s gives %s to %s.\n", who, what, whom) != 3)
      return;
   if(whom != "Harry")
      return;
   if(what == "firebreather" || what == "special" ||
      what == "beer" || what == "bottle") {

      rand = random(4);

      if(rand == 0) {
         if(random(10) > 6) {
            respond("sigh I guess you're gonna kill me now.");
	    respond("drop all");
            call_other(this_object(), "init_command", "west");
         }
      }
      if(rand == 1) {
         call_other(this_object(), "init_command", "drink " + what);
      }
      if(rand == 2) {
         respond("drop all");
      }
      if(rand == 3) {
         obj = this_object()->present(what);
         if (obj) {
            obj->move(who);
            notify("Harry returned the " + what + " to " + who + ".\n");
         }
      }
   } else if(what == "corpse") {
      respond("say HEY, bury your corpses yourself, asshole.");
      obj = this_object()->present(what);
      if (obj) {
         obj->move(who);
         notify("Harry returned the " + what + " to " + who + ".\n");
      }
   } else {
      respond("say Thank you very much, sir.");
   }
}

void monster_died() {
   object obj, b;
   int num;

/* XXX  drop all make sure bottles break.... */

   if (num) {
      notify("There is a crushing sound of bottles breaking, " +
      "as the body falls.\n");
   }
}

int down() {
   call_other(this_player(), "move_player", DIR + "/rooms/station");
   return 1;
}
