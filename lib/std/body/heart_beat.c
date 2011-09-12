static int heal_rate;
static int heal_amount;
static int heal_time;
int player_age;

int    is_fighting( void );
void   do_fight( void );
int    is_alive();
int    is_dead();
int    add_stat( string statname, int amt );
int    query_stat( string statname );


void set_heal_rate( int rate ) {
   heal_rate = rate;
}

int query_heal_rate( void ) {
  return( heal_rate );
}

void set_heal_step( int amt ) {
   heal_amount = amt;
}

int query_heal_step( void ) {
  return( heal_amount );
}

void create()
{
  EVENT_D->subscribe_event("heart_beat");
  heal_time = 0;
  heal_rate = 10;
  heal_amount = 2;
  if( !intp( player_age ) ) {
    player_age = 0;
  }
}

void event_heart_beat( void ) {
  object sp;

  sp = this_player();
  set_this_player(this_object());

  if( this_object()->is_alive()) {
    heal_time++;
    if( heal_time > heal_rate ) {
        heal_time = 0;
        if (this_object()->query_hp() < this_object()->query_max_hp())
            this_object()->increase_hp( random( heal_amount ) + 1 );
        if (this_object()->query_mana() < this_object()->query_max_mana())
            this_object()->increase_mana( random( heal_amount ) + 1 );
        if (this_object()->query_end() < this_object()->query_max_end())
            this_object()->increase_end( random( 2 * heal_amount ) + 1 );
    }
  }
  /* Check here to see is we are in combat, if so, continue battle */
  if( this_object()->is_fighting() > 0) {
    this_object()->do_fight();
  } else {
    if( function_object( "event_wander", this_object()) ) {
      call_other( this_object(), "event_wander" );
    }
  }

  set_this_player(sp);

  if(!this_object()->is_player())  /* NPC routines */ {
    if(this_object()->is_dead()) {
      EVENT_D->unsubscribe_event("heart_beat");
      this_object()->destruct();
    }
  } else  /* Player routines */ {
    if(this_object()->query_idle() < 60)  /* A player ages when not idle */
    player_age += HEART_BEAT_INTERVAL;
  }
}


nomask int query_age(varargs int raw) {
  return player_age;
}
