void usage() {
   write("Usage: eval [-h] STRING\n");
   write("Evaluate the lpc code: STRING.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\t.me  is shorthand for this_player()\n");
   write("\t.here  is shorthand for this_environment()\n");
   write("Examples:\n");
   write("\teval write(\"My hp: \" + this_player()->query_hp() + \"\\n\");\n");
   write("\teval .here->tell_room(.me,\"Hi\\n\");\n");
   write("\teval return 5 + 5;\n");
   write("\teval write(\"Sirdude's HP: \" + \n" +
      "\t\tUSER_D->find_player(\"sirdude\")->query_hp() + \"\\n\");\n");
}

void main(string src, varargs mixed args ...) {
   object obj;
   string err;
   mixed result;
   int str_size;

   if (src == "-h") {
      usage();
      return;
   }

   src = replace_string(src, ".me", "this_player()");
   src = replace_string(src, ".here", "this_environment()");
   str_size = strlen(src);
   if (str_size && src[(str_size - 1)] != ';')
      src += ";";
   err = catch(obj =
      compile_object("/wiz/" + this_player()->query_name() + "/obj/eval_ob",
	 "# include <float.h>\n# include <limits.h>\n" +
	 "# include <status.h>\n# include <trace.h>\n" +
	 "# include <type.h>\n\n" +
	 "private mixed exec_fun(mixed args...) {\n" + "    mixed " +
	 "a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;\n" +
	 "args = args[0];\n" + src + "}\n" +
	 "mixed *exec(object player, varargs mixed argv...) {\n" +
	 "int ticks;\n" + "mixed returnval;\n" + "argv = argv[0];\n" +
	 "ticks = status()[ST_TICKS];\n" + "returnval = exec_fun(argv);\n" +
	 "ticks = ticks - status()[ST_TICKS];\n" +
	 "return ({ ticks, returnval });\n" + "}\n"), result =
      obj->exec(this_player(), args));

   if (obj)
      destruct_object(obj);

   if (err) {
      write("Error: " + err + ".\n");
   } else {
      if (result[1] || intp(result[1])) {
	 write("Result: \n" + dump_value(result[1]) + "\n");
      } else {
	 write("Result: \n" + "<nil>" + "\n");
      }
      write("Ticks used: " + (string) result[0] + "\n");
   }
}
