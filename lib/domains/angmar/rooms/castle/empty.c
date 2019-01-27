#include "../../domain.h"

inherit "/std/room";

static object spirit;
static int is_summoning;

void summon_spirit(void) {
   is_summoning = TRUE;
   call_out("message1", 3);
}

void message1(void) {
   tell_room(this_object(), "You get an uneasy feeling...");
   call_out("message2", 3);
}

void message2(void) {
   tell_room(this_object(),
             "Something is very wrong in here. Your brain is screaming " +
             "to you to get out of here immediately!");
   call_out("message3", 3);
}

void message3(void) {
   tell_room(this_object(),
             "A shimmering light slowly appears in front of you.");
   call_out("message4", 2);
}

void message4(void) {
   tell_room(this_object(),
             "A half transparent luminous spirit hovers in the air.");
   call_out("message5", 1);
}

void message5(void) {
   tell_room(this_object(),
         "The spirit begins to wail in a hair-raising voice.");
   spirit = clone_object(DIR + "/monsters/spirit.c");
   spirit->setup();
   spirit->move(this_object());
   is_summoning = FALSE;
}

void tell_room(object originator, string str, varargs mixed obj ...) {
   object intruder, spirit;
   string intruder_name;

   if (sscanf(str, "%s enters.\n", intruder_name) == 1) {
      intruder = present(lowercase(intruder_name));
      if (!spirit && intruder->is_player() && !is_summoning) {
         summon_spirit();
      }
   }

   ::tell_room(originator, str, obj);
}

void setup(void) {
   add_area(AREA);
   add_area(CASTLE_AREA);
   set_short("An empty room");
   set_long("You are in a totally empty room. You feel the presence of "+
            "a magic force here... ");

   add_exit("west", CASTLE_ROOMS + "/corridor.c");

   add_item("force", "You can't see it, but you can feel it.");
   add_item("magic force", "You can't see it, but you can feel it.");
}
