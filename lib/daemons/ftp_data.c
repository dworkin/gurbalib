inherit M_CONNECTION;

object "/daemons/ftp_session" prev;
string callback;
string read_callback;
int connected;


void FTPLOG( string str ) {
  write_file( "/logs/ftpd", ctime( time() ) + " : " + str );
}

void message_done( void ) {
  if( prev )
    call_other( prev, callback );
}

void create( void ) {
  callback = "FTP_write";
  connected = 0;
}

void set_callback( string str ) {
  callback = str;
}

void open( varargs int port ) {
  connected = 1;
}

int is_connected( void ) {
  return( connected );
}

void close( varargs int force ) {
  if( read_callback == "FTP_stor" )
    call_other( prev, "FTP_write" );
  destruct_object(this_object());
}

void start_connection( string ip, int port, int type ) {
  connect( ip, port, "tcp" );
}

void send_data( mixed data ) {
  prev = previous_object();
  send_message( data );
/*
  if( send_message( -1 ) == 0 )
    call_out( "message_done", 1 );
*/
  /* message_done(); */
}

void set_read_callback( string func ) {
  prev = previous_object();
  read_callback = func;
}

void receive_message( string str ) {
  call_other( prev, read_callback, str );
}

void terminate() {
  disconnect();
}

