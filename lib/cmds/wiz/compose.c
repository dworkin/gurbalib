void usage () {
   write("Usage compose [-h]");
   write("Scan the objects in your inventory and create an autoload string.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: aload\n");
}

// XXX I'm assuming this needs work still.  Currently autoloading is not used.
// look at std/m_autoload_filename.c and std/modules/m_autoload_filename.c
//  for more info, also why both???  should be in one location...

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

