void usage() {
  write("Usage: graph [-h] DIR\n");
  write("prints dot compatible output of a graph of the directory you " +
    "specify.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void print_node(string room, string dir) {
   mapping *exits;
   string *keys, filepath;
   int i,maxi,len;
   object obj;

   obj = find_object(dir + "/" + room);

// XXX maybe need to do more work here to load the room?

   if (obj) {
      len = strlen(dir);
      exits = obj->query_exits();
      keys = obj->query_exit_indices();
      if (exits) {
         maxi = sizeof(keys);
         for(i=0;i<maxi;i++) {
            if (0) {  // XXX check to see if front matches dir if so cut it ...
               filepath = exits[keys[i]];
            } else {
               filepath = exits[keys[i]];
            }
            write("\t" + keys[i] + " -> " + filepath + ";\n");
         }
      }
   } else {
      write("# Failed to load " + $dir + "/" + room + "\n");
   }
}

void main( string str ) {
  int i;

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

  /* Look at ls it does this and then does str + "/*"
     I don't think we need both... it's odd... */
  files = get_dir( str );
  if( !files ) {
    write( "Dir:" + str + " is empty.\n");
    return;
  }

  /* do the work here... */
  i = sizeof(files);
  while(i>0) {
     i--;
     write("# Looking at : " + str + "/" + files[i] + "\n");
     write("digraph G {\n");
     print_node(files[i],str);
     write("}\n");
     write("# End: str\n");
  }
}

