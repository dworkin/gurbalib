void main( string str ) {
   string file, argument, rest;
   object ob;
   
   str = this_player()->query_autoload_string();
   while(str && str != "*^!") {
      if (sscanf(str, "%s:%s^!%s", file, argument, rest) != 3) {
         write("Autoload string corrupt.\n");
         return;
      }
      str = rest;
      if( file_exists( file ) ) {
         write("file = "+file+"\n");
         write("argument = "+argument+"\n");
         write("rest = "+rest+"\n\n");
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

