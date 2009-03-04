/* Just a small command to show the rooms short description and filename.
 *
 * Fudge
 */

void main( string arg ) {
  write( this_environment()->query_brief() + ": [" + this_environment()->file_name() + "]\n" );
}
