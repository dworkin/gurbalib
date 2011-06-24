void usage() {
  write("Usage: zap [-h] PLAYER [PERCENT]\n");
  write("Zap the given player: PLAYER, reducing their HP by PERCENT.\n");
  write("PERCENT should be > 0 and < 100.\n");
  write("If PERCENT is missing, we assume you want to kill your target.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object target;
  int i, sz;
  int target_hp, target_damage;
  string who, target_name;
  int perc;

  if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( sscanf( str, "%s %d", who, perc ) != 2 ) {
    who = str;
    perc = 100;
  }

  if (perc <= 0) {
      write("Zapping with no power is useless.");
      return;
  }
  if (perc > 100) {
      write("Zapping with more than 100% damage is silly; setting to 100%.");
      perc = 100;
  }

  target = this_environment()->present(who);

  if (!target) {
    write("Cant find " + who + "\n");
    return;
  }

  target_hp = target->query_hp();
  target_name = target->query_id();
  target_damage = (target_hp * perc) / 100;

  write(target->query_id() + " has " + target_hp + " hitpoints");
  write(target->query_id() + " is going to receive " + target_damage + 
	" damage");

    switch(perc) {
      case 1..20 : this_player()->targetted_action(
			"$N $vlook slightly annoyed at $T.", target);
                   target->message( "You feel uncomfortable.");
                   break;
      case 21..40 : this_player()->targetted_action( 
			"$N $vlook intensely at $T.", target);
                    target->message( "Your skin burns.");
                    break;
      case 41..60 : this_player()->targetted_action( 
			"$N $vlook angry at $T", target);
                    target->message( "You feel as if you're hit by a tree.");
                    break;
      case 61..80 : this_player()->targetted_action( 
			"$N $vstare at $T for a while", target);
                    target->message( 
			"Your head hurts, and your nose begins to bleed.");
                    break;
      case 81..99 : this_player()->targetted_action( 
			"Sparks fly as $N $vstare intensely at $T", target);
                    target->message( 
			"Your brain starts to ooze out of your ears.");
                    break;
      case 100 : this_player()->targetted_action( 
			"$N $vgive $T the evil eye.", target);
                 target->message("Your head explodes.");
                 break;
    }
  /*this_player()->simple_action("$N $vgive " + target->query_id() + 
	" a very nasty look..."); */
  target->decrease_hp(target_damage);

  if (target->query_hp() < 1) {
    target->simple_action( "$N $vfall to the ground...dead." );
    target->message( "You have died." );
    target->die();
  } else {
    write(target->query_id() + " is left with " + target->query_hp() + 
	" hitpoints.");
  }
}

