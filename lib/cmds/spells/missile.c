#define COST 10

void usage() {
   write("Usage: cast missile [-h] TARGET\n");
   write("Casts a magic missile at TARGET\n");
   write("This spell requires " + COST + " mana.\n");
   write("This spell does 1-5 damage to TARGET.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void missile(object thisp, object target) {
   int x;

   x = random(5) + 1;
   thisp->decrease_mana(COST);
   write("You shoot a magick missile out your hands at " +
      target->query_name() + " damaging them for " + x + " hp.\n");
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
