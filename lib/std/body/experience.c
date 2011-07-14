int experience;
int level;

void create( void ) {
}

int ready_for_next_level() {
   int tmpexp;

   tmpexp = level * level * 2000;

   if (experience > tmpexp) {
      return 1;
   }
   return 0;
}

void increase_level() {
   level += 1;
   write("Congragulations, you just achieved level: " + level + "\n");
}

void increase_expr( int expr ) {
   if(expr < 0 ) {
      expr = expr * -1;
   }
   experience += expr;
   if( experience < 0 ) {
      experience = 0;
   }
   if (ready_for_next_level()) {
	increase_level();
	write("Congragulations, you just went up a level...\n");
	level += 1;
   }
}

void decrease_expr( int expr ) {
   if(expr > 0 ) {
      expr = expr * -1;
   }
   experience -= expr;
   if( experience < 0 ) {
      experience = 0;
   }
}

void set_expr( int expr ) {
   experience = expr;
   if( experience < 0 ) {
      experience = 0;
   }
}

int query_expr( void ) {
  return( experience );
}

int query_level(void) {
   if (level < 1) level = 1;
   return( level );
}

