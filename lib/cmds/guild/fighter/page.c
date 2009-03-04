void main( string str ) {
   object ob;

   string page;

   page = this_player()->query_name() + "s page";
   ob = this_player()->query_environment()->find_object( page );

   if( ob ) {
      ob->parse(str);
   } else {
      ob = clone_object("/std/page.c");
      if( ob ) {
	 ob->move( this_player()->query_environment() );
	 ob->set_master(this_player());
	 ob->setup();
	 this_player()->simple_action( "$N $vyell for $p page." );
      } else {
	 this_player()->simple_action( "$N $vyell for $p page, but he can't be yelling loud enough.");
      }
   }
}

