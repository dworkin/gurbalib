string autoload_string;

string query_autoload_string( void ) {
   return autoload_string;
}

void set_autoload_string( string str ) {
   autoload_string = str;
}

void clone_autoload_objects( string str ) {
   string file, argument, rest;
   object ob;
    
   while(str && str != "*^!") {
      if (sscanf(str, "%s:%s^!%s", file, argument, rest) != 3) {
         write("Autoload string corrupt.\n");
         return;
      }
      str = rest;
      if( file_exists( file ) ) {
        /* write("file = "+file+"\n");
         write("argument = "+argument+"\n");
         write("rest = "+rest+"\n\n"); */
         ob = clone_object( file );
         if( ob ) {
            ob->move( this_player()->query_environment() );
            ob->setup();
            if( argument ) {
               ob->initialize_autoload( argument );
            }
            ob->move( this_player() );
         } 
      }
   }
}



void compose_autoload_string( void ) {
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
   this_player()->set_autoload_string(str);
}




