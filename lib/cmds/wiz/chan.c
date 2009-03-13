/* An interface to the channel daemon
 * 
 * Fudge
 */


void main( string str ) {
  string chan;
  string cmd;


  if( !str || str == "" ) {
    write( "Usage: chan <channel> </command>\n Command can be join, leave, quit, new, admin, wiz, permanent, who, list, info, or delete.\n" );
    return;
  }
  if( sscanf( str, "%s %s", chan, cmd ) != 2 ) {
    chan = str;
    cmd = "/info";
  }

  CHANNEL_D->chan_cmd( chan, cmd );
}
