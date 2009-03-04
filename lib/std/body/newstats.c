#define VALID_STATS ({ "str", "con", "end", "dex", "agl", "aim", "int", "wis", "per", "cha", "luc", "spr", "god" })

mapping base_stats;
mapping bonus_stats;

string query_valid_base_stat( string statname );
string query_valid_bonus_stat( string statname );
int  query_stat( string statname );
int  query_base_stat( string statname );
int  query_bonus_stat( string statname );
void trim_base_stat(string statname); 
void trim_bonus_stat(string statname); 
int  add_base_stat( string statname, int amt ); 
int  add_bonus_stat( string statname, int amt ); 
int  set_base_stat( string statname, int amt ); 
int  set_bonus_stat( string statname, int amt );
mixed *query_all_stats(); 
void  initialize_base_stats(); 
void  initialize_bonus_stats();


string query_valid_base_stat( string statname )
{
   if( base_stats[statname] )
      return statname;
}

string query_valid_bonus_stat( string statname )
{
   if( bonus_stats[statname] )
      return statname;
}

int  query_stat( string statname )
{
   if( !statname ) {
      return 0;
   }
   if( !base_stats ) {
      base_stats = ([ ]);
   }
   if( !bonus_stats ) {
      bonus_stats = ([ ]);
   }
   return ( base_stats[statname] + bonus_stats[statname] );
}

int  query_base_stat( string statname )
{
   if( !statname ) {
      return 0;
   }
   if( !base_stats ) {
      base_stats = ([ ]);
   }
   return base_stats[statname];
}

int  query_bonus_stat( string statname )
{
   if( !statname ) {
      return 0;
   }
   if( !bonus_stats ) {
      bonus_stats = ([ ]);
   }
   return bonus_stats[statname];
}

void trim_base_stat(string statname) 
{
   int max, min;
   max = this_object()->query_race_object()->query_base_stat_maximum(statname);    
   min = this_object()->query_race_object()->query_base_stat_minimum(statname); 
   if( base_stats[statname] < min) {
      base_stats[statname] = min;
   }
   else if( base_stats[statname] > max) {
      base_stats[statname] = max;
   }
}   

void trim_bonus_stat(string statname) 
{
   int max, min;
   max = this_object()->query_race_object()->query_bonus_stat_maximum(statname);    
   min = this_object()->query_race_object()->query_bonus_stat_minimum(statname); 
   if( bonus_stats[statname] < min) {
      bonus_stats[statname] = min;
   }
   else if( bonus_stats[statname] > max) {
      bonus_stats[statname] = max;
   }
}

int  add_base_stat( string statname, int amt ) 
{
   if( !base_stats ) {
      base_stats = ([ ]);
   }
   if( member_array( statname, VALID_STATS ) == -1 ) {
      return 0;
   }
   if( !base_stats[statname] ) {
      base_stats[statname] = amt;
   }
   else {
      base_stats[statname] += amt;
   }
   trim_base_stat(statname); 
   return 1;
}

int  add_bonus_stat( string statname, int amt ) 
{
   if( !base_stats ) {
      bonus_stats = ([ ]);
   }
   if( member_array( statname, VALID_STATS ) == -1 ) {
      return 0;
   }
   if( !bonus_stats[statname] ) {
      bonus_stats[statname] = amt;
   }
   else {
      bonus_stats[statname] += amt;
   }
   trim_bonus_stat(statname); 
   return 1;
}
 
int  set_base_stat( string statname, int amt ) 
{
   if( !base_stats ) {
      base_stats = ([ ]);
   }
   if( member_array( statname, VALID_STATS ) == -1 ) {
      return 0;
   }
   base_stats[statname] = amt;
   trim_base_stat(statname); 
   return 1;
}

int  set_bonus_stat( string statname, int amt ) 
{
   if( !bonus_stats ) {
      bonus_stats = ([ ]);
   }
   if( member_array( statname, VALID_STATS ) == -1 ) {
      return 0;
   }
   bonus_stats[statname] = amt;
   trim_bonus_stat(statname); 
   return 1;
}
   
mixed *query_all_stats()
{
   mixed  *ret;
   string *stat_names;
   int     i;

   stat_names = map_indices( base_stats );
   ret = ({ });
   for( i=0; i < sizeof( stat_names ); i++ )
   {
      ret += ({ ({ stat_names[i], base_stats[stat_names[i]], bonus_stats[stat_names[i]]  }) });
   }
   return( ret );
}


void  initialize_base_stats() 
{
this_object()->set_base_stat( "str", this_object()->query_race_object()->query_base_stat_minimum("str") );
this_object()->set_base_stat( "con", this_object()->query_race_object()->query_base_stat_minimum("con") );
this_object()->set_base_stat( "end", this_object()->query_race_object()->query_base_stat_minimum("end") );

this_object()->set_base_stat( "dex", this_object()->query_race_object()->query_base_stat_minimum("dex") );
this_object()->set_base_stat( "agl", this_object()->query_race_object()->query_base_stat_minimum("agl") );
this_object()->set_base_stat( "aim", this_object()->query_race_object()->query_base_stat_minimum("aim") );

this_object()->set_base_stat( "int", this_object()->query_race_object()->query_base_stat_minimum("int") );
this_object()->set_base_stat( "wis", this_object()->query_race_object()->query_base_stat_minimum("wis") );
this_object()->set_base_stat( "per", this_object()->query_race_object()->query_base_stat_minimum("per") );

this_object()->set_base_stat( "cha", this_object()->query_race_object()->query_base_stat_minimum("cha") );
this_object()->set_base_stat( "luc", this_object()->query_race_object()->query_base_stat_minimum("luc") );
this_object()->set_base_stat( "spr", this_object()->query_race_object()->query_base_stat_minimum("spr") );

this_object()->set_base_stat( "god", this_object()->query_race_object()->query_base_stat_minimum("god") );
}

void  initialize_bonus_stats() 
{
this_object()->set_bonus_stat( "str", 0 );
this_object()->set_bonus_stat( "con", 0 );
this_object()->set_bonus_stat( "end", 0 );

this_object()->set_bonus_stat( "dex", 0 );
this_object()->set_bonus_stat( "agl", 0 );
this_object()->set_bonus_stat( "aim", 0 );

this_object()->set_bonus_stat( "int", 0 );
this_object()->set_bonus_stat( "wis", 0 );
this_object()->set_bonus_stat( "per", 0 );

this_object()->set_bonus_stat( "cha", 0 );
this_object()->set_bonus_stat( "luc", 0 );
this_object()->set_bonus_stat( "spr", 0 );

this_object()->set_bonus_stat( "god", 0 );
}


