void usage() {
  write("Usage: aload [-h] [FILE]\n");
  write("Not sure how this works yet....XXX\n");
  write("If no FILE is given display current autoload string.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: compose???\n");
}

void main( string str ) {
   string file, argument, rest;
   object ob;

   if ( !str || str == "" ) {
      str = this_player()->query_autoload_string();
      write ("Your autoload_string is: "+str+"\n");
   }
   if (sscanf(str, "-%s",str)) {
      usage();
      return;
   }

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

