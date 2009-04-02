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

  if(str && str == "-v") verbose = 1;
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

