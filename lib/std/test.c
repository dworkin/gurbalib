string autoload;


void clone_autoload_objects(string str) {
   string file, argument, rest;
   object ob;

   while(str && str != "") {
      if (sscanf(str, "%s:%s^!%s", file, argument, rest) != 3) {
         write("Autoload string corrupt.\n");
         return;
      }
      str = rest;
      /*   ob = find_object(file);
      if (!ob)
         continue;  */
      ob = clone_object(file);
      if (argument) {
         ob->initialize_autoload(argument);
      }
      ob->move( this_player() );
   }
}


void compose_autoload_string( void ) {
   object ob;
   string str;
   object *inv;
   int i;
   
   autoload = "";
   inv = this_player()->query_inventory();
   if( sizeof( inv ) ) {
      for( i=0; i < sizeof( inv ); i++ ) {
         str = inv[i]->query_autoload();
         if ( str && (str != "") ) {
            autoload = autoload + str + "^!";
         }
      }
   }
   /* terminate autoload string */
   autoload = autoload + "EOL^!";
}
