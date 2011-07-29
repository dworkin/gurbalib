void usage() {
  write("Usage: graph [-h] DIR\n");
  write("prints dot compatible output of a graph of the directory you " +
    "specify.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void print_node(string room, string dir) {
   mapping exits;
   string *keys, filepath, tmp;
   int i,maxi,len;
   object obj;

   dir = dir + "/";
   obj = find_object(dir + room);

   if (!obj) {
       obj = compile_object(dir + room);
   }

   if (obj) {
      len = strlen(dir);
      exits = obj->query_exits();
      keys = obj->query_exit_indices();
      if (exits) {
         maxi = sizeof(keys);
         for(i=0;i<maxi;i++) {
	    tmp = exits[keys[i]] + ".c";
	    filepath = replace_string(tmp,dir,"");
            write("\t\"" + room + "\" -> \"" + filepath + 
               "\" [label = \"" + keys[i] + "\"];\n");
         }
      }
   } else {
      write("# Failed to load " + dir + room + "\n");
   }
}

void main( string str ) {
  int i, size;
  string *files;
  mixed *dirent;

  if( !str || str == "" ) {
    usage();
    return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  str = normalize_path( str, this_player()->query_env( "cwd" ) );

  if( !str || str == "" ) {
    write( "Access denied.\n" );
    return;
  }

 if( strlen(str) > 1 && str[strlen(str)-1] == '/' ) {
    str = str[..strlen(str)-2];
  }
    
  if( file_exists( str ) != -1 ) {
    write( "Dir not found.\n" );
    return;
  }

  dirent = get_dir( str + "/*.c" );

  if( !dirent ) {
    write( "Dir:" + str + " is empty.\n");
    return;
  }
  files = dirent[0];

  /* do the work here... */
  size = sizeof(files);
  write("# Looking at : " + str + "/" + files[i] + "\n");
  write("# Use dot -Tpng thisfile.dot -o thisfile.png
  write("digraph G {\n");

  for(i=0;i < size; i++) {;
     print_node(files[i],str);
  }
  write("}\n");
  write("# End: str\n");
}

