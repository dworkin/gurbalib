void main( string str) {
  string path;
  object ob;
  object *usr;

  int i;
  int flag;

  string what;
  string who;

  /*  string *words;

      words = explode( str, " " );

      who = words[0]; 
      what = words[1]; */

 sscanf( str, "%s %s", who, what );

  usr = USER_D->query_users();
  flag = 0;
  
  if (strlen(str) > 2) {
    if( (str[strlen(str)-2] == '.') 
	&& (str[strlen(str)-1] == 'c') )
      str = str[..strlen(str)-3];
  }

  path = this_player()->query_env( "cwd" );  

  for( i = 0; i < sizeof( usr ); i++) {
    if( usr[i]->query_name() == who ) {
      flag = 1;
      path = normalize_path( what, path);
      if( path == "" ) {
	write( "Access denied.\n" );
	return;
      }

      if( file_exists( path + ".c") ) {
	ob = clone_object( path );
	  if( ob ) {
	    ob->setup();
	    ob->move(usr[i]->query_player() );
	    usr[i]->query_player()->message( capitalize(article(ob->query_id())) + " " + ob->query_id() + " suddenly appears in your pockets.\n" );
	    write( "You send " + article(ob->query_id() ) + " " + ob->query_id() + " into " + capitalize(who) + "'s pockets.\n");
	  }
      } else {
	write( "File not found.\n" );
      }
    }
  }
  if (flag == 0){
    write( capitalize(who) + " not found.\n");
  }
}
