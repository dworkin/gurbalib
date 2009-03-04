private static mapping msg;
private static mapping subject;
private static mapping ob;

void main( string str ) {

  if( !msg ) {
    msg = ([ ]);
    subject = ([ ]);
    ob = ([ ]);
  }
  ob[this_player()->query_name()] = this_environment()->find_object( "board" );
  if( !ob[this_player()->query_name()] ) {
    write( "Try writing a message at a message board.\n" );
    return;
  } 
  if( str == "" ) {
    subject[this_player()->query_name()] = "(none)";
  } else {
    subject[this_player()->query_name()] = str;
  } 

  write( " \nPlease enter your text below.\n"
	 + "'.' without quotes on a blank line to end. ~a to abort.\n"
	 + "------------------------------------------------------------------------------\n");
  this_player()->input_to_object( this_object(), "enter_line" );
  this_player()->set_editing( 1 );
  msg[this_player()->query_name()] = "";
}

void enter_line( string line ) {
  if( line != "." && line != "**" && line != "~a" ) {
    if( !msg[this_player()->query_name()] ) {
      msg[this_player()->query_name()] = line + "\n";
    } else {
      msg[this_player()->query_name()] = msg[this_player()->query_name()] + line + "\n";
    }
    this_player()->input_to_object( this_object(), "enter_line" );
  } else {
    if( line == "~a" ) {
      write( " \nMessage aborted.\n" );
    } else {
      ob[this_player()->query_name()]->add_message( this_player()->query_name(), subject[this_player()->query_name()], msg[this_player()->query_name()] );
      write( " \nMessage posted.\n" );
    }
    this_player()->set_editing( 0 );
    this_player()->write_prompt();
    this_environment()->tell_room( this_player(), capitalize(this_player()->query_name()) + " posts a new message.\n" );
  }
}
