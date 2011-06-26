void usage() {
  write("Usage: read [-h] THING\n");
  write("Allows you to read readable things.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object ob;
  string *lines;

  if ( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  ob = this_environment()->present( str );

  if( ob ) {
    if( ob->is_readable() ) {  
      if( ob->can_read( this_player() ) ) {
        ob->do_read( this_player() );
      } else {
        write( "You can't read that." );
      }
    } else {
      write( "You can't read that." );
    }
  } else {
    ob = this_environment()->present( "board" );
    if( !ob ) {
      write( "Try reading a message at a message board.\n" );
      return;
    }
    
    if( !str || str == "" ) {
      write( "Read what?" );
      return;
    }

    if( str == "next" ) {
      str = "" + (this_player()->query_board_read( ob->query_board_id() ) + 1);
    } 
  
    if( ob->query_msg_exists( str ) == 1 ) {
      lines = explode( ob->query_message( str ), "\n" );
      write( implode( lines[..3], "\n" ) );
      this_player()->more(lines[4..] );
      this_player()->set_board_read( ob->query_board_id(), str2val( str ) );
    } else {
      write( "No such message.\n" );
    }
    return;
  }
}
