#include <type.h>

void usage() {
   string *lines;

   lines = ({ "Usage: warmboot [-h]" });
   lines += ({ "" });
   lines += ({ "Similar to a reboot but keeps the system running." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twarmboot" });
   lines += ({ "See also:" });
   lines += ({ "\tcheck, clean, clone, dest, eval, dumpstate, rebuild, " +
      "shutdown, update" });

   this_player()->more(lines);
}

#define LAST_STAGE 3
int stage;

#define CHECKS ({ "validate_kernel", "validate_user", "validate_player" })

static int validate_kernel() {
   return 0;
}

static int validate_user() {
   if (find_object("/obj/user"))
      return 222;
}

static int validate_player() {
   if (find_object("/obj/player"))
      return 222;
}

static string validate_upgrade() {
   int req, i, sz;

   req = 0;

   for (i = 0, sz = sizeof(CHECKS); i < sz; i++) {
      req = call_other(this_object(), CHECKS[i]);

      if (req) {
	 return CHECKS[i] + " failed.\nPlease revert to revision " + req +
	    ", do a warmboot, and then try this upgrade again.";
      }
   }
}

void main(string str) {
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (stage) {
      write("busy");
      return;
   }

   if (!require_priv("system")) {
      write("You need admin permissions to do that.");
      return;
   }

   write("Performing warm boot.");
   write("Recompiling the warmboot command..");
   compile_object(base_name());

   stage = call_out("next_stage", 0, 0, this_player());
}

private int virtual_object(mixed ob) {
   if (typeof(ob) == T_OBJECT) {
      ob = file_name(ob);
   }
   switch (ob) {
      case "/sys/lib/auto.c":
	 return 1;
      default:
	 return 0;
   }
}

static string post_kernel_upgrade(object p) {
   if (find_object("/daemons/user_d")) {
      destruct_object(find_object("/daemons/user_d"));
   }
}

static string post_world_upgrade(object p) {
   if (!find_object(USER_D)) {
      call_other(USER_D, "upgraded");
   }
}

static int upgrade_uobj(string * files, int verbose) {
   int pos, sz;
   string fn, on;

   for (pos = 0, sz = sizeof(files); pos < sz; pos++) {
      fn = files[pos];
      if (sscanf(fn, "%s.c", on) != 1) {
	 on = fn;
      }

      if (!virtual_object(fn) && !file_exists(fn)) {
	 if (find_object(on)) {
	    this_player()->message("Warning: " + files[pos] +
	       " is loaded but there is no source for it, cannot recompile.");
	 } else {
	    this_player()->message("Ignoring " + files[pos]);
	 }
	 continue;
      }

      if (COMPILER_D->test_inheritable(files[pos])) {
	 if (find_object(on, 1)) {
	    compile_library(files[pos]);
	 }
      } else if (find_object(on)) {
	 compile_object(files[pos]);
      } else {
	 write("Warning: " + files[pos] + " not recompiled!");
      }
   }
   return pos;
}

atomic static void rebuild_critical(object p) {
   object ob;

   p->message("Atomically recompiling the driver, " +
      "auto and compiler objects...");

   catch { compile_object(DRIVER); }:{
      rethrow();
   }
   catch { compile_library(AUTO); }:{
      rethrow();
   }
   catch { compile_library("/kernel/lib/auto-kernel"); }:{
      rethrow();
   }
   catch { ob = compile_object(COMPILER_D); }:{
      rethrow();
   }
   catch { ob = compile_object(SECURE_D); }:{
      rethrow();
   }
   ob->junk();
}

static void rebuild_world(object p) {
   int pos, sz, total, verbose;
   mapping edges;
   string *users;

   DRIVER->update_tls_size();

   p->message("Rebuilding remaining objects.");

   edges = COMPILER_D->query_upqueue();

   rlimits(250; -1) {
      if (edges) {
	 if (edges["kernel"]) {
	    total += upgrade_uobj(edges["kernel"], verbose);
	    edges["kernel"] = nil;
	 }

	 users = map_indices(edges);

	 for (pos = 0, sz = sizeof(users); pos < sz; pos++) {
	    total += upgrade_uobj(edges[users[pos]], verbose);
	 }
      }
   }
   COMPILER_D->clear_upqueue();

   p->message("A total of " + total + " objects was upgraded.");
}

void next_stage(int count, object player) {
   string error;

   stage = 0;
   switch (count) {
      case 0:
	 error = validate_upgrade();
	 if (!error) {
	    error = catch(rebuild_critical(player));
	 } else {
	    player->message(error);
	 }
	 break;
      case 1:
	 error = post_kernel_upgrade(player);
	 if (error) {
	    player->message(error);
	 }
	 break;
      case 2:
	 error = catch(rebuild_world(player));
	 break;
      case 3:
	 error = post_world_upgrade(player);
	 if (error) {
	    player->message(error);
	 }
	 break;
   }

   if (error) {
      player->message("Something went wrong, aborting.");
      if (caught_error()) {
	 player->tell(caught_error(1));
      }
      rethrow();
   } else if (count != LAST_STAGE) {
      stage = call_out("next_stage", 0, ++count, player);
   } else {
      player->message("Done.");
   }
}
