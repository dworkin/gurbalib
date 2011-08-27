void usage () {
	write("XXXX");
}

void main( string str ) {
   object ob;
   string tmp;
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
   write("compose_autoload_string = "+str+"\n");
   this_player()->set_autoload_string(str);
}

