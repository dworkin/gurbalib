void main( string str ) {
  mapping mudlist;
  string *muds;
  int i;
  string tmp;
  string line;
  string *lines;

  mudlist = IMUD_D->query_mudlist();

  if( !mudlist ) {
    write( "Empty mudlist. Wait a few minutes and try again.\n" );
    return;
  }

  muds = map_indices( mudlist );

  write("Size: " + sizeof(muds) + "\n");

  lines = ({ "Up Mud                Address         Port  Lib            Status             " });
  lines += ({ "-----------------------------------------------------------------------------" });

  for( i=0; i < sizeof( muds ); i++ ) {

    line = "";

    if( mudlist[muds[i]][0] != -1 ) {
      continue;
    }

    if( sizeof(mudlist[muds[i]]) < 9 ) {
       continue;
    }

    tmp = "U   ";
    line += tmp[..2];

    tmp = muds[i] + "                   ";
    line += tmp[..17] + " ";

    tmp = mudlist[muds[i]][1] + "                ";
    line += tmp[..15];

    tmp = "" + mudlist[muds[i]][2] + "      ";
    line += tmp[..4] + " ";

    tmp = mudlist[muds[i]][5] + "              ";
    line += tmp[..13] + " ";

    tmp = mudlist[muds[i]][9] + "                      ";
    line += tmp[..19];

    lines += ({ line });
  }

  this_player()->more( lines );
}
