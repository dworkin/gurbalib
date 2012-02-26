void usage() {
  write("Usage: evaluate [-h] OBJ\n");
  write("Evaluate the specified object and print out what you think it is " +
    "worth.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

// XXX moved this from dwarven race specific command need to use skills instead
// and give dwarves the skill by default....

void main (string str) {
  int chance;
  int roll;
  int diff; /*Difference between roll and chance*/
  int dev; /*Deviation from the actual value*/
  int value;
  object obj;

  if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  obj = this_environment()->present( lowercase( str ) );

  if(!obj) {
    write("You don't see " + ob + " here.");
    return;
  }

  if (!obj->is_living() && obj->query_value() ) {
    
    chance = this_player()->query_skill( "evaluate" );
    roll = random(5000);
    if (roll > chance) {
      diff = roll - chance;
      dev = random(diff);
      if (random(2) == 1) {
	value = obj->query_value() * (1+(diff / 100));
      } else {
	value = obj->query_value() + (1-(diff / 100));
      }
    } else {
      value = obj->query_value();
    }
    write("You estimate that the value is about " + value + "gold pieces.\n");
  } else {
    write( "You can't evaluate that." );
  }
}
 
