inherit M_COMMAND;

#define COST 10
#define SKILLREQUIRED 15

string *usage(void) {
   string *lines;

   lines = ({ "Usage: cast cure [-h] [TARGET]" });
   lines += ({ "" });
   lines += ({ "Casts cure light wounds on TARGET" });
   lines += ({ "If no target is given you heal yourself." });
   lines += ({ "This spell requires " + COST + " mana." });
   lines += ({ "This spell heals 1-5 hit points on TARGET." });
   lines += ({ "You need to have a skill level of " + SKILLREQUIRED + 
      " before you can cast this spell " });
   lines += ({ "on other players." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcast cure" });
   lines += ({ "\tcast cure sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "cast");
}

int max_hp(object target) {
   if (target->query_hp() >= target->query_max_hp()) {
      return 1;
   }
   return 0;
}

void cure(object thisp, object target) {
   int x;

   x = random(5) + 1;
   thisp->decrease_mana(COST);

   if (max_hp(target) || target->is_dead()) {
      write("Your spell has no effect.\n");
      this_object()->targeted_action("A soft glow envelopes $N, " +
         "and then fizzles out.\n");
      return;
   }

   if (thisp == target) {
      write("You concentrate and heal yourself for " + x + " hp.\n");
      this_object()->targeted_action("A soft glow envelopes $N, " +
         "as they cure their wounds.\n");
   } else {
      write("You lay your hands on " + target->query_name() +
         " healing them for " + x + " hp.\n");
      this_object()->targeted_action("A soft glow envelopes " +
         target->query_name() + "as $N cures their wounds.\n");
   }
   target->increase_hp(x);
}

void do_spell(object thisp, string target) {
   object tar;

   if (empty_str(target)) {
      tar = thisp;
   } else if (target == "-h") {
      this_player()->more(usage());
      return;
   } else {
      tar = this_environment()->present(target);
   }
   if (thisp->query_mana() < COST) {
      write("You do not have enough mana to cast that.\n");
   } else {
      if (tar) {
         if (tar == thisp) {
            cure(thisp, tar);
         } else if (thisp->query_skill("spell/cure") >= SKILLREQUIRED) {
            cure(thisp, tar);
         } else {
            write("You are not skilled enough at cure to cast it on others.\n");
         }
      } else {
         write("You want to cast cure on who?\n");
      }
   }
}

