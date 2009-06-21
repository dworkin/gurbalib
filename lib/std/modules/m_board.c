inherit OBJECT;

string board_id;
string data_dir;

mixed *msgs;

void add_message( string from, string subj, string msg );

void set_board_id( string str ) {
  board_id = str;
}

void set_data_dir( string dir ) {
  data_dir = dir;
}

string query_data_dir() {
  return data_dir;
}

string query_board_id( void ) {
  if(board_id)
  return( board_id );
}

void default_data_dir() {
  string * stuff;

  stuff = explode(base_name(), "/");

  switch(stuff[0]) {
    case "domains" : 
    case "wiz"     :
      data_dir = "/" + stuff[0] + "/" + stuff[1];
      break;
    case "kernel"  :
      data_dir = "/kernel";
      break;
    case "sys"     :
      data_dir = "/sys";
      break;
    default :
      data_dir = "";
      break;
  }
  data_dir += "/data/boards";
}

void save_me( void ) {
  if(!data_dir) {
    default_data_dir();
  }
  unguarded( "save_object", data_dir+ "/" + query_board_id() + ".o" );
}

void restore_me( void ) {
  if(!data_dir) {
    default_data_dir();
  }
  unguarded( "restore_object", data_dir + "/" + query_board_id() + ".o" );
}


void create( void ) {
  ::create();
}

void check_restore( void ) {
  if( !msgs )
    restore_me();
  if( !msgs ) {
    msgs = ({ });
  }
}

void add_message( string from, string subj, string msg ) {
  check_restore();
  msgs += ({ ({capitalize(from), capitalize(subj), ctime( time() ), msg }) });
  save_me();
}

int query_message_count( void ) {
  check_restore();
  return( sizeof( msgs ) );
}

int query_new_message_count( void ) {
  check_restore();
  return( query_message_count() - this_player()->query_board_read( board_id ) ); 
}

int query_msg_exists( string num ) {
  int i;

  check_restore();

  i = str2val(num) - 1;
  
  if( i > sizeof( msgs ) - 1  || i < 0 ) {
    return( 0 );
  }
  return( 1 );
}

string query_message( string num ) {
  int i;
  string msg;
  i = str2val(num) - 1;

  if( i > sizeof( msgs ) || i < 0 ) {
    return( "Message doesn't exist.\n" );
  }

  save_me();

  msg = " \nPoster: %^CYAN%^" + msgs[i][0] + "%^RESET%^\n";
  msg += "Subject: %^YELLOW%^" + msgs[i][1] + "%^RESET%^\n";
  msg += "Date: %^GREEN%^" + msgs[i][2] + "%^RESET%^\n";
  msg += "------------------------------------------------------------------------------\n";
  msg += msgs[i][3];
  return( msg );
}

string query_message_list( string who ) {
  string msg;
  string tmp;
  string from;
  string subj;
  string date;
  int i;
  int num;

  check_restore();

  msg = " \nNum    From        Subject                            Date\n" +
    "------------------------------------------------------------------------------\n";

  num = this_player()->query_board_read( board_id ) - 10;
  if( num < 0 )
    num = 0;

  for( i = num; i < sizeof( msgs ); i++ ) {
    tmp = "        " + (i+1);
    tmp = tmp[strlen(tmp)-4..];
    from = (string) msgs[i][0] + "                                          ";
    from = from[..10];
    subj = msgs[i][1] + "                                                   ";
    subj = subj[..33];
    date = msgs[i][2] + "                                    ";
    date = date[..25];
    if( i == this_player()->query_board_read( board_id ) ) {
      msg += "[" + tmp + "]>" + from + " " + subj + " " + date + "\n";
    } else {
      msg += "[" + tmp + "] " + from + " " + subj + " " + date + "\n";
    }
  }
  return(msg);
}
