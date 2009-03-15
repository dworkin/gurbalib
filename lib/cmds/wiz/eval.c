void main( string str ) {
  string filename;
  object obj;
  string err;
  mixed result;

  filename = "/tmp/" + this_player()->query_name();

  remove_file( filename + ".c" );

  str = replace_string( str, ".me", "this_player()" );
  str = replace_string( str, ".here", "this_environment()" );

  write_file( filename + ".c" ,
	      "# include <float.h>\n# include <limits.h>\n" +
	      "# include <status.h>\n# include <trace.h>\n" +
	      "# include <type.h>\n\n" +
	      "mixed exec(object player, varargs mixed argv...) {\n" +
	      "    mixed " +
	      "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;\n\n" +
	      "    return(" + str + ");\n}\n");
  err = catch(obj = compile_object(filename),
	      result = obj->exec(this_player(), str)
	      );

  if( obj )
    destruct_object( obj );

  if (err) {
    write("Error: " + err + ".\n");
  } else {
    if(result || intp(result)) {
      write( "Result: \n" + dump_value(result, ([ ])) + "\n" );
    } else {
      write( "Result: \n" + "<nil>" + "\n" );
    }
  }    
  remove_file( filename + ".c" );

}
