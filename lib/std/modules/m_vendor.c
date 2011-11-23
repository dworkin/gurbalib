inherit MONSTER;
inherit M_MESSAGES;
inherit M_TRIGGERS;

static mapping stored_items;
static int will_buy;
static int will_sell;
static int restock_delay;

int is_vendor( void ) {
  return( 1 );
}

void set_restock_delay( int delay ) {
  restock_delay = delay;
  call_out( "restock", delay );
}

void restock( void ) {
  this_object()->setup();
}

void set_will_buy( int will ) {
  will_buy = will;
}

int query_will_buy( void ) {
  return( will_buy );
}

void set_will_sell( int will ) {
  will_sell = will;
}

int query_will_sell( void ) {
  return( will_sell );
}

void do_sell( object player, string what ) {
  string *objs;
  object obj;
  int i;
  int found;

  objs = map_indices( stored_items );


  found = 0;
  for( i = 0; i < sizeof( objs ); i++ ) {

    obj = clone_object( objs[i] );
    if( obj ) {
      obj->move( this_object() );
      obj->setup();

      if( obj->query_id() == what && found != 1 ) {
	/* Found the object */
	this_object()->other_action( this_object(), 
          "$N $vgive $t $o", player, obj );
	obj->move( player );
	stored_items[objs[i]] = stored_items[objs[i]] - 1;
	found = 1;
      } else { 
	obj->query_environment()->remove_object( obj );
	obj->destruct();
      }
    } 
  }

  if( found == 0 ) {
    player->message( "That item is out of stock." );
  }
}

void do_buy( object player, object what ) {
  string name;

  name = what->base_name();

  player->targetted_action( "$N $vgive $t $o", this_object(), what );

  what->move( this_object() );
  what->query_environment()->remove_object( what );
  what->destruct();

  stored_items[name] = stored_items[name] + 1;

}

void add_item( string name, int amount ) {

  if( amount == 0 )
    amount = 1;

  if( !stored_items )
    stored_items = ([ ]);

  stored_items[name] = amount;
}

string query_list( void ) {
  string str;
  string num;
  string *objs;
  object obj;
  int i;

  if( !stored_items )
    stored_items = ([ ]);

  objs = map_indices( stored_items );
  str = "";

  for( i = 0; i < sizeof( objs ); i++ ) {

    obj = clone_object( objs[i] );
    if( obj ) {

      obj->move( this_object() );
      obj->setup();

      num = "   " + stored_items[objs[i]];
      num = num[strlen(num)-3..];

      if( !obj->query_proper_name() ) {
	if( !obj->query_adj() || obj->query_adj() == "" ) {
	  str += " %^CYAN%^[" + num + "]%^RESET%^ " + obj->query_id() + ", " + 
            obj->query_value() + " crowns\n";
	} else {
	  str += " %^CYAN%^[" + num + "]%^RESET%^ " + obj->query_adj() + " " + 
            obj->query_id() + ", " + obj->query_value() + " crowns\n";
	}
      } else {
	str += " %^CYAN%^[" + num + "]%^RESET%^ " + obj->query_proper_name() + 
          ", " + objs->query_value() + " crowns\n";
      }
      obj->query_environment()->remove_object( obj );
      obj->destruct();
    }
  }
  return( str );
}

void do_list( object player ) {
  write( "%^BLUE%^=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" +
    "-=-=-=-=-=-=-=-=-=-=-=-%^RESET%^\n\n" );
  write( query_list() );
  write( "%^BLUE%^\n=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" +
    "-=-=-=-=-=-=-=-=-=-=-=-=-%^RESET%^\n" );
}
