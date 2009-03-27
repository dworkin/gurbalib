#include <type.h>

inherit OBJECT;

static object *inventory;

void create( void ) {
  inventory = ({ });
}

int is_container( void ) {
  return( 1 );
}

void object_arrived( object obj ) {

}

void object_removed( object obj ) {

}

int receive_object( object obj ) {
  obj = (object "/std/object") obj;
  if( !inventory )
    inventory = ({ obj });
  else
    inventory += ({ obj });

  object_arrived( obj );
  return 1;
}

int remove_object( object obj ) {
  if( !inventory ) 
    return 0;
  else 
    inventory -= ({ obj });
  object_removed( obj );
  return 1;
}

object *query_inventory( void ) {

  return( inventory );
}

object find_object_num( string name, int num ) {
  int i,j;
  string *ids;
  if(inventory)
	for( i = 0; i < sizeof( inventory ); i ++ ) {
		ids = inventory[i]->query_ids();
		if( ids ) {
			for( j = 0; j < sizeof( ids ); j ++ ) {
				if( lowercase( ids[j] ) == lowercase( name ) ) {
					num--;
					if( num == 0 ) 
						return( inventory[i] );
				}
			}
		}
	}
}

object find_object( string name ) {
	return( find_object_num( name, 1 ) );
}

object find_adj_object_num( string adj, string name, int num ) {
  int i,j,k;
  string *ids;
  string *adjs;
  for( i = 0; i < sizeof( inventory ); i ++ ) {
    ids = inventory[i]->query_ids();
		if( ids ) {
			for( j = 0; j < sizeof( ids ); j ++ ) {
				if( lowercase( ids[j] ) == lowercase( name ) ) {
					if( inventory[i]->is_adj( adj ) == 1 ) {
						num--;
						if( num == 0 )
							return( inventory[i] );
					}
				}
			}
		}
	}
  return( nil );
}

object find_adj_object( string adj, string name ) {
	return( find_adj_object_num( adj, name, 1 ) );
}

object find_adjs_object_num( string *adj, string name, int num ) {
  int i,j,k;
	string *ids;
	string *adjs;
	for( i = 0; i < sizeof( inventory ); i ++ ) {
		ids = inventory[i]->query_ids();
		if( ids ) {
			for( j = 0; j < sizeof( ids ); j ++ ) {
				if( lowercase( ids[j] ) == lowercase( name ) ) {
					int nFound;
					nFound = 1;
					for( k = 0; k < sizeof( adj ); k++ ) {
						if( !inventory[i]->is_adj( adj[k] ) )
							nFound = 0;
					}
					if( nFound ) {
						num--;
						if( num == 0 )
							return( inventory[i] );
					}
				}
			}
		}
	}
	return( nil );
}

object find_adjs_object( string *adj, string name ) {
	return( find_adjs_object_num( adj, name, 1 ) );
}

void set_objects( mapping obs ) {
  object ob;
  string *filename;
  string name;
  int i;
  int num;

  filename = map_indices( obs );
  for( i = 0; i < sizeof( filename ); i++ ) {
    if( strstr( filename[i], "#" ) != -1 ) {
      name = filename[i][0..strstr( filename[i], "#" )-1];
    } else {
      name = filename[i];
    }
    if( typeof( obs[filename[i]] ) == T_ARRAY ) {    

      ob = clone_object( name );
      ob->move( object_name( this_object() ) );
      ob->setup();
      ob->mudlib_setup( obs[filename[i]] );
    } else {
      num = obs[filename[i]];
      while( num > 0 ) {
        ob = clone_object( name );
        ob->move( object_name( this_object() ) );
        ob->setup();
        num--;
      }
    }
  }
}

