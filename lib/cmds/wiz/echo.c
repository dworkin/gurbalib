
void main( string str){
  string msg;

  msg = str;

  this_player()->query_environment()->tell_room( this_player(), "\n" + msg + "\n" );
  write( "You echo to the room: '" + msg + "'.\n");
}
