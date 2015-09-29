#include "../domain.h"

inherit "/std/monster";
inherit "/std/modules/m_triggers";

#define INTERVAL 8
#define RESETINTERVAL 8

int count;
object solved_by, wrong_by;

void setup(void) {
   set_name("player");
   set_gender( "male" );
   set_short("Go player");
   set_long("A man sitting beside a go board, concentrating on a problem.\n" +
      "He looks as if he wants help.  Why not look at his problem,\n" +
      "and tell him where to play?\n");

   set_race("human");
   set_level(10);
   set_hit_skill("combat/unarmed");
   set_skill("combat/unarmed", 100);
   set_skill("combat/defense", 100);
   set_aggressive(0);
}

void do_extra_actions() {
   int x;
   
   x = query_environment()->query_current_problem();

   count = count + 1;
   if (x < 3) {
      if (count > INTERVAL) {
         switch(random(5)) {
            case 0:
               respond("say Hm. This is tricky!");
               break;
            case 1:
               respond("say The moron who wrote this book didn't deal with " +
                  "this problem.");
               break;
            case 2:
               respond("say A throw in here should just be wasted.");
               break;
            case 3:
               respond("say This group is more alive than I am.");
               break;
            default:
               respond("say This is simple using oi-otoshi.");
               break;
         }
         count = 0;
      }
   } else {
      if (count > RESETINTERVAL) {
         count = 0;
         query_environment()->set_current_problem(0);
      }
   }
}

int make_move(int prob) {
   int i;

   if (solved_by) {
      respond("say Right! That works!");
      query_environment()->tell_object(this_object(),
         "He immediately plays out a new problem.");
      solved_by->message("You feel that you have gained some experience.");

      solved_by->increase_expr(prob * 100);

      solved_by = nil;
      query_environment()->set_current_problem( prob + 1);
   }
   if (wrong_by) {
      respond("say No, that doesn't work.");
      query_environment()->tell_room(this_object(),
         "He sinks back into his deep thought.");
      wrong_by = nil;
   }
}

void outside_message(string str) {
   string name, what;
   int prob;
   object room, who;

   str = ANSI_D->strip_colors(str);
   if (sscanf(str, "%s tells you: Play %s.\n", name, what) == 2 ||
      sscanf(str, "%s says: Play %s.\n", name, what) == 2) {
      room = query_environment();

      if (!room) {
         return;
      }
      who = room->present(name);

      if (!who) {
         return;
      }

      prob = room->query_current_problem();
      if (prob == 0) {
         if (what == "b1" || what == "b 1" || what == "1b" || what == "1 b") {
            solved_by = who;
         } else {
            wrong_by = who;
         }
      } else if (prob == 1) {
         if (what == "b2" || what == "b 2" || what == "2b" || what == "2 b") {
            solved_by = who;
         } else {
            wrong_by = who;
         }
      } else if (prob == 2) {
         if (what == "d3" || what == "d 3" || what == "3d" || what == "3 d") {
            solved_by = who;
         } else {
            wrong_by = who;
         }
      }

      query_environment()->tell_room(this_object(),
         "The go player contemplates a propsed play.");
      if (solved_by) {
         solved_by->message("Arne PISS OFF!");
      } else if (wrong_by) {
         wrong_by->message("Arne PISS OFF!");
      }
      make_move(prob);
   } else {
      if (sscanf(str, "%s tells you: %s\n", name, what) == 2 ||
         sscanf(str, "%s says: %s\n", name, what) == 2) {
         respond("say What?");
      }
   }
}

