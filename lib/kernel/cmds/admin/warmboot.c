#define LAST_STAGE 1
int stage;

#define CHECKS ({ "validate_kernel", "validate_user", "validate_player" })

static int validate_kernel() {
  return 0;
}

static int validate_user() {
  if( find_object( "/obj/user" ) )
    return 222;
}

static int validate_player() {
  if( find_object( "/obj/player" ) )
    return 222;
}

static string validate_upgrade() {
  int req;
  int i, sz;

  req = 0;

  for( i = 0, sz = sizeof(CHECKS); i < sz; i++ ) {
    req = call_other( this_object(), CHECKS[i] );
 
    if( req ) {
      return CHECKS[i] + " failed.\nPlease revert to revision "+req+", do a warmboot, and then try this upgrade again.";
    }
  }
}

void main(string str) {
  if(stage) {
    write("busy");
    return;
  }

  write("Performing warm boot.");
  write("Recompiling the warmboot command..");
  compile_object(base_name());

  stage = call_out("next_stage",0,0,this_player());
}

static int upgrade_uobj(string * files, int verbose) {
  int pos, sz;

  for( pos = 0, sz = sizeof( files ); pos < sz; pos++ ) {
    if( COMPILER_D->test_inheritable( files[pos] ) ) {
      if( find_object(files[pos],1) ) { 
        compile_library( files[pos] );
      } 
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

  DRIVER->update_tls_size();

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
      error = validate_upgrade();
      if(!error) {
        error = catch( rebuild_critical(player) );
      } else {
        player->message(error);
      }
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
    if(find_object("/obj/user")) {
      call_out("convert_user_object",0);
    } else {
      player->message("Done.");
    }
  }
}

static void convert_user_object() {
  object ob, next;

  ob = find_object("/obj/user");

  if(!ob) return;

  ob = ob->next_clone();

  rlimits( MAX_DEPTH; -1 ) {
    while(ob) {
      next = ob->next_clone();
      ob->uobj_convert();
      ob = next;
    }
  }
  destruct_object(find_object("/obj/user"));
  destruct_object(find_object("/obj/player"));
/*
  ob = find_object("/std/user",1);
  if(ob) destruct_object(ob);
  ob = find_object("/std/player",1);
  if(ob) destruct_object(ob);
*/
}

