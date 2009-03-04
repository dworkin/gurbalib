/* Autoload routines for use in player.c */

static string autoload_string;

string query_autoload_string( void ) {
   return autoload_string;
}

void set_autoload_string( string str ) {
   autoload_string = str;
}

string compose_autoload_string( void ) {
   object ob;
   string str, tmp;
   object *inv;
   int i;
   
   str = "";
   inv = this_player()->query_inventory();
   if( sizeof( inv ) ) {
      for( i=0; i < sizeof( inv ); i++ ) {
         tmp = inv[i]->query_autoload_filename();
         if ( tmp && (tmp != "") ) {
            str = str + tmp + "^!";
         }
      }
   }
   /* terminate autoload string */
   str = str + "*^!";
   return str;
}
