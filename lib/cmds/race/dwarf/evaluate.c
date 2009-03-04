void main (string ob) {
  int chance;
  int roll;
  int diff; /*Difference between roll and chance*/
  int dev; /*Deviation from the actual value*/
  int value;
  object obj;

  /*Todo: Add so that it finds the 'ob' object and stores it in the 'obj' variable.*/
  obj = this_environment()->find_object( lowercase( ob ) );

  if (!ob->is_living() && ob->query_value() ) {
    
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
    
  
