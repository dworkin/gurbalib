#define COST 10

void usage() {
  write("Usage: cast missle [-h] TARGET\n");
  write("Casts a magic missle at TARGET\n");
  write("This spell requires " + COST + " mana.\n");
  write("This spell does 1-5 damage to TARGET.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void missle(object thisp, object target) {
  int x;

  x = random(5) + 1;
  thisp->decrease_mana(COST);
  write("You shoot a magick missle out your hands at " + target->query_name() +
      " damaging them for " + x + " hp.\n");
  this_object()->targetted_action("A soft glow shoots from $N's hands and " +
      "hits " + target->query_name() + ".\n");
  target->decrease_hp(x);
}

void do_spell(object thisp, string target) {
  object tar;

  if (!target || target == "" || target == "-h") {
     usage();
     return;
  } else {
    tar = this_environment()->present(target);
  }
  if (tar) {
     if (tar == thisp) {
        write("You can't cast a magic missle at yourself.\n");
     } else {
        missle(thisp,tar);
     }
  } else {
     write("You want to cast magic missle on who?\n");
  }
}

