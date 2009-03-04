int strength;
int intelligence;
int constitution;
int wisdom;
int dexterity;
int charisma;

void create( void ) {
  
}

void initialize_stats( ) {
  strength = random( this_object()->query_race_object()->query_racial_max_str() - 
		     this_object()->query_race_object()->query_racial_min_str()) + 
             this_object()->query_race_object()->query_racial_min_str();
  intelligence = random( this_object()->query_race_object()->query_racial_max_int() - 
			 this_object()->query_race_object()->query_racial_min_int()) + 
                 this_object()->query_race_object()->query_racial_min_int();
  constitution = random( this_object()->query_race_object()->query_racial_max_con() - 
			 this_object()->query_race_object()->query_racial_min_con()) + 
                 this_object()->query_race_object()->query_racial_min_con();
  wisdom = random( this_object()->query_race_object()->query_racial_max_wis() - 
		   this_object()->query_race_object()->query_racial_min_wis()) + 
           this_object()->query_race_object()->query_racial_min_wis();
  dexterity = random( this_object()->query_race_object()->query_racial_max_dex() - 
		      this_object()->query_race_object()->query_racial_min_dex()) + 
              this_object()->query_race_object()->query_racial_min_dex();
  charisma = random( this_object()->query_race_object()->query_racial_max_cha() - 
		     this_object()->query_race_object()->query_racial_min_cha()) + 
              this_object()->query_race_object()->query_racial_min_cha();
}

int query_str( void ) {
  return( strength + this_object()->query_race_object()->query_racial_str() );
}

int query_int( void ) {
  return( intelligence + this_object()->query_race_object()->query_racial_int() );
}

int query_con( void ) {
  return( constitution + this_object()->query_race_object()->query_racial_con() );
}

int query_wis( void ) {
  return( wisdom + this_object()->query_race_object()->query_racial_wis() );
}

int query_dex( void ) {
  return( dexterity + this_object()->query_race_object()->query_racial_dex() );
}

int query_cha( void ) {
  return( charisma + this_object()->query_race_object()->query_racial_cha() );
}