void main( string dir1, string dir2, string dir3 ) {
   string error;

   if( dir3 ) {
      error = this_environment()->body_exit( this_player(), dir1+" "+dir2+" "+dir3 );
   }
   else if( dir2 ) {
      error = this_environment()->body_exit( this_player(), dir1+" "+dir2 );
   }
   else {
      error = this_environment()->body_exit( this_player(), dir1 );
   }
   
   if( error ) {
      write( error );
   }
}

