inherit M_COMMAND;

#define COST 10

string *usage(void) {
   string *lines;

   lines = ({ "Usage: cast missile [-h] TARGET" });
   lines += ({ "" });
   lines += ({ "Casts a magic missile at TARGET" });
   lines += ({ "This spell requires " + COST + " mana." });
   lines += ({ "This spell does 1-5 damage to TARGET." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcast missile rabbit" });
   lines += ({ "\tcast missile sirdude" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "cast");
}

void missile(object thisp, object target) {
   int x;

   x = random(5) + 1;
   thisp->decrease_mana(COST);
   write("You shoot a magick missile out your hands at " +
      target->query_name() + " damaging them for " + x + " hp.\n");
   this_object()->targeted_action("A soft glow shoots from $N's hands and " +
      "hits " + target->query_name() + ".\n");
   target->decrease_hp(x);
}

void do_spell(object thisp, string target) {
   object tar;

   if (empty_str(target) || target == "-h") {
      this_player()->more(usage());
      return;
   } else {
      tar = this_environment()->present(target);
   }
   if (tar) {
      if (tar == thisp) {
         write("You can't cast a magic missile at yourself.\n");
      } else {
         if (this_player()->query_mana() >= COST) {
            missile(thisp, tar);
         } else {
            write("You do not have enough mana to cast that.\n");
         }
      }
   } else {
      write("You want to cast magic missile on who?\n");
   }
}

