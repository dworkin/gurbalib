#define LAST_STAGE 1
int stage;

void main(string str) {
  if(stage) {
    write("busy");
    return;
  }

  write("Performing warm boot.");
  stage = call_out("next_stage",0,0,this_player());
}

static int upgrade_uobj(string * files, int verbose) {
  int pos, sz;

  for( pos = 0, sz = sizeof( files ); pos < sz; pos++ ) {
    if(COMPILER_D->test_inheritable(files[pos])) {
      compile_library( files[pos] );
    } else {
      compile_object( files[pos] );
    }
  }
  return pos;
}

atomic static void rebuild_critical(object p) {
  object ob;

  p->message("Atomically recompiling the driver, auto and compiler objects...");
  catch { compile_object(DRIVER); } : { rethrow(); }
  catch { compile_library(AUTO); } : { rethrow(); }
  catch { compile_library("/kernel/lib/auto-kernel"); } : { rethrow(); }
  catch { ob = compile_object(COMPILER_D); } : { rethrow(); }
  ob->junk();
}

static void rebuild_world(object p) {
  int pos, sz, total, verbose;
  mapping edges;
  string * users;

  p->message("Rebuilding remaining objects.");

  edges = COMPILER_D->query_upqueue();

  rlimits( 250; -1 ) {
    if(edges) {
      if(edges["kernel"]) {
        total += upgrade_uobj( edges["kernel"], verbose );
        edges["kernel"] = nil;
      }

      users = map_indices( edges );

      for( pos = 0, sz = sizeof( users ); pos < sz; pos++ ) {
        total += upgrade_uobj( edges[users[pos]], verbose );
      }
    }
  }
  COMPILER_D->clear_upqueue();

  p->message( "A total of "+total+" objects was upgraded." );
}

void next_stage(int count, object player) {
  string error;

  stage = 0;
  switch(count) {
    case 0    :
      error = catch( rebuild_critical(player) );
      break;
    case 1    :
      error = catch( rebuild_world(player) );
      break;
  }

  if(error) {
    player->message("Something went wrong, aborting.");
    rethrow();
  } else if(count != LAST_STAGE) {
    stage = call_out("next_stage",0,++count,player);
  } else {
    player->message("Done");
  }
}

