void main( string src, varargs mixed args...) {
  object obj;
  string err;
  mixed result;
  int str_size;

  src = replace_string( src, ".me", "this_player()" );
  src = replace_string( src, ".here", "this_environment()" );
  str_size = strlen(src);
  if(str_size && src[ (str_size-1)] != ';')
    src += ";";
  err = catch(obj = compile_object("eval_ob", 
	      "# include <float.h>\n# include <limits.h>\n" +
	      "# include <status.h>\n# include <trace.h>\n" +
	      "# include <type.h>\n\n" +
	      "mixed exec(object player, varargs mixed argv...) {\n" +
		  "int ticks;\n"+
	      "    mixed " +
	      "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;\n"+
		  "argv = argv[0];\n" +
	      src + "\n}"),
		result = obj->exec(this_player(), args) );

  if( obj )
    destruct_object( obj );

  if (err) {
    write("Error: " + err + ".\n");
  } else {
    if(result || intp(result)) {
      write( "Result: \n" + dump_value(result) + "\n" );
    } else {
      write( "Result: \n" + "<nil>" + "\n" );
    }
  } 

}
