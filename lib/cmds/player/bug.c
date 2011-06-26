void usage() {
  write("Usage: bug [-h] MSG\n");
  write("Allows you to submit a bug (MSG) to the system.\n");
  write("We can't fix bugs unless we know about them.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

private static mapping msg;
private static mapping subject;
private static mapping ob;

void main( string str ) {

  if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( !msg ) {
    msg = ([ ]);
    subject = ([ ]);
    ob = ([ ]);
  }
  ob[this_player()->query_name()] = "/rooms/bug_room"->present( "board" );
  if( !ob[this_player()->query_name()] ) {
    write( "Unable to locate the bug board. Tell a wizard.\n" );
    return;
  } 
  if( !str || str == "" ) {
    subject[this_player()->query_name()] = "[" + this_player()->query_environment()->file_name() + "]";
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
      write( " \nBug report sendt! Thank you.\n" );
      CHANNEL_D->chan_send_string( "wiz", capitalize(this_player()->query_name()), "sends off a bugreport.", 1 );
      
    }
    this_player()->set_editing( 0 );
    this_player()->write_prompt();
    this_environment()->tell_room( this_player(), capitalize(this_player()->query_name()) + " lets Fudge know how much he sucks.\n" );
  }
}
