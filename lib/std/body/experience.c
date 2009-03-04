int experience;

void create( void ) {
}

void increase_expr( int expr ) {
   if(expr < 0 ) {
      expr = expr * -1;
   }
   experience += expr;
   if( experience < 0 ) {
      experience = 0;
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

void add_expr( int expr ) {
   experience += expr;
   if( experience < 0 ) {
      experience = 0;
   }
}


int query_expr( void ) {
  return( experience );
}
