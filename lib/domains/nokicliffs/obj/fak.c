#include "../domain.h"
#define HEALING_AMT (15 + random(15))

inherit "/std/object";
inherit NOKICLIFFS_HEALING_LIB;

void setup(void) {
   set_id("first aid kit");
   add_id("kit");
   set_short("Individual first aid kit");
   set_long("An individual first aid kit has enough supplies " +
      "for one time usages. You can 'bandage' yourself or " +
      "a comrade to help recovery from injury.");
   set_gettable(1);
   set_value(5);
   set_weight(1);
   add_action("bandage_cmd", "bandage");
}

int bandage_cmd(string str) {
   object doc, patient;
   int    was_bandaged;
   string msg;

   doc = this_player();
   if (empty_str(str)) {
      patient = this_player();
   } else {
      if (str == "me" || str == "self" || str == "myself") {
         patient = this_player();
      } else {
         patient = this_player()->query_environment()->present(str);
      }
   }
   if (!patient) {
      write("Bandage who?");
      return 1;
   }
   if (patient == doc) {
      msg = "$N $vapply a first aid kit.";
   } else {
      msg = "$N $vapply a first aid kit to $T.";
   }
   was_bandaged = recover_hp(doc, patient, HEALING_AMT, msg);
   if (!was_bandaged) {
      write("How kind, but really it's not necessary.");
   } else {
      destruct();
   }
   return 1;
}
