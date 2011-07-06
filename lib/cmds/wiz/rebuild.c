void usage() {
  write("Usage: zap [-h] [-v]\n");
  write("Rebuild the objects on the mud.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("\t-v\tenable Verbose mode.\n");
  write("See also: warmboot, clone, update\n");
}

static int upgrade_uobj(string * files, int verbose) {
  int pos, sz;

  for( pos = 0, sz = sizeof( files ); pos < sz; pos++ ) {
    if(verbose) write("Upgrading "+files[pos]);
    if(COMPILER_D->test_inheritable(files[pos])) {
      compile_library( files[pos] );
    } else {
      compile_object( files[pos] );
    }
  }
  return pos;
}

void main(string str) {
  int pos, sz, total, verbose;
  mapping edges;
  string * users;

  edges = COMPILER_D->query_upqueue();

  if(str && str == "-v") {
     verbose = 1;
  } else if (sscanf(str, "-%s",str)) {
     usage();
     return;
  } else if (str && str != "") {
     usage();
     return;
  }
  rlimits( 250; -1 ) {
    if(edges) {
      if(edges["kernel"]) {
        write("User: kernel");
        total += upgrade_uobj( edges["kernel"], verbose );
        edges["kernel"] = nil;
      }

      users = map_indices( edges );

      for( pos = 0, sz = sizeof( users ); pos < sz; pos++ ) {
        write("User: "+users[pos]);
        total += upgrade_uobj( edges[users[pos]], verbose );
      }
    }
  }
  COMPILER_D->clear_upqueue();

  write( "A total of "+total+" objects was upgraded." );
}

