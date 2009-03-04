#include <status.h>

void main( string str ) {

  this_player()->set_title( str );
  out( "New title: " + this_player()->query_title() + "\n" );
}


