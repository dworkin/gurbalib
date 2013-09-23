inherit M_COMMAND;
inherit "/sys/lib/modules/m_getopt";

string *resubmit;

void usage() {
   string *lines;

   lines = ({ "Usage: rebuild [-h] [-v] [-c] [user,...]" });
   lines += ({ " " });
   lines += ({ "Rebuild the objects on the mud." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-v\tenable Verbose mode." });
   lines += ({ "\t-c\tinclude 'core' users (kernel, system, game)" });
   lines += ({ "\t-a\tinclude all users for which objects are compiled." });
   lines += ({ "\tuser can be any user for which objects are compiled," });
   lines += ({ "\tit defaults to yourself if not specified." });
#ifdef SECURITY_COMPILER_RW
   lines += ({ "" });
   lines += ({ "\tOnly objects to which you have write access will be" });
   lines += ({ "\tcompiled." });
#endif
   lines += ({ "Examples:" });
   lines += ({ "\trebuild" });
   lines += ({ "\trebuild -v -c" });
   lines += ({ "\trebuild -v game" });
   lines += ({ "\trebuild -a" });
   lines += ({ "See also:" });

   if (query_admin(this_player())) {
      lines += ({ "\tcheck, checkmud, clean, clone, dest, eval, graph, " +
         "update, warmboot" });
   } else {
      lines += ({ "\tcheck, clean, clone, dest, eval, graph, " +
         "update" });
   }

   this_player()->more(lines);
}

static int resubmit_upqueue(string f) {
   COMPILER_D->add_upqueue(f);
   return 1;
}

static int upgrade_uobj(string * files, int verbose) {
   int pos, sz, uc;

   uc = 0;

   for (pos = 0, sz = sizeof(files); pos < sz; pos++) {
      if (!valid_write(files[pos])) {
         resubmit += ({ files[pos] });
         continue;
      } else if (verbose > 2) {
	 write("Upgrading " + files[pos]);
      }

      uc++;

      if (COMPILER_D->test_inheritable(files[pos])) {
         catch {
	    compile_library(files[pos]);
         } : {
            error("Error compiling " + files[pos]);
         }
      } else {
         catch {
	    compile_object(files[pos]);
         } : {
            error("Error compiling " + files[pos]);
         }
      }
   }
   return uc;
}

static void main(string str) {
   int pos, sz, total, verbose, core, all;
   mapping edges;
   string *users;
   string *wanted;
   string tmp;
   string *file;

   str = parse_for_options(str);

   if (query_parse_error()) {
      write("Parse error: " + query_parse_error());
      return;
   }

   if (test_option("help")) {
      usage();
      return;
   }

   verbose = (test_option("verbose") ? query_option("verbose") : 0);
   core = test_option("core");
   all = test_option("all");
   file = query_option("file");

   if (!all) {
      if (core) {
         wanted = ({"kernel","system","game"});
      } else {
         wanted = ({ });
      }

      if (str && strlen(str)) {
         wanted |= explode(str," ");
      }

      if (!sizeof(wanted)) {
         wanted = ({ this_player()->query_name() });
      }
   } else {
      wanted = nil;
   }

   resubmit = ({ });

   if (core && (!file || !sizeof(file))) {
      file = ({ AUTO });
   }

   if (verbose) {
      write("rebuild: verbose level is " + verbose);
      write("rebuild: going to perform the following actions:");

      if (file && sizeof(file)) {
         for (pos=0, sz=sizeof(file); pos<sz; pos++) {
            write("Recompile " + file[pos]);
         }
      }

      if (core && !all) {
         write("rebuild all outdated core objects.");
      }

      if (all) {
         write("rebuild all outdated objects.");
      }
      
      if (!all) {
         users = wanted;
         if (core) {
            users -= ({"kernel","system","game"});
         }
         if (sizeof(users)) {
            write("rebuild all outdated user objects for " + implode(users, ",") + ".");
         }
      }
      write("---");
   }

   if (file && sizeof(file)) {
      for (pos=0, sz=sizeof(file); pos<sz; pos++) {
         if (!valid_write(file[pos])) {
             write("No write access to " + file[pos] + ", aborted.");
             return;
         } else if (tmp = catch(compile_library(file[pos]))) {
             write(tmp);
             return;
         } else if (verbose) {
             write("Recompiled " + file[pos]);
         }
      }
   }

   edges = COMPILER_D->query_upqueue();

   rlimits(250; -1) {
      if (edges) {
	 if (edges["kernel"] && (!wanted || (sizeof(wanted & ({"kernel"})) != 0)) 
            && valid_write("/kernel/data")) {
	    if (verbose > 1) write("Rebuilding kernel.");
	    total += upgrade_uobj(edges["kernel"], verbose);
	    edges["kernel"] = nil;
	 } else if (edges["kernel"]) {
            resubmit += edges["kernel"];
            edges["kernel"] = nil;
         }

         if (edges["system"] && (!wanted || (sizeof(wanted & ({"system"})) != 0))
            && valid_write("/sys/data")) {
            if (verbose > 1) write("Rebuilding system.");
            total += upgrade_uobj(edges["system"], verbose);
            edges["system"] = nil;
         } else if (edges["system"]) {
            resubmit += edges["system"];
            edges["system"] = nil;
         }

         if (edges["game"] && (!wanted || (sizeof(wanted & ({"game"})) != 0))
            && valid_write("/daemons/data")) {
            if (verbose > 1) write("Rebuilding game.");
            total += upgrade_uobj(edges["game"], verbose);
            edges["game"] = nil;
         } else if (edges["game"]) {
            resubmit += edges["game"];
            edges["game"] = nil;
         }

	 users = map_indices(edges);

	 for (pos = 0, sz = sizeof(users); pos < sz; pos++) {
            if (!wanted || (sizeof(wanted & ({ users[pos] })) != 0)) {
               if (verbose > 1) {
                  write("Rebuilding for user " + users[pos]);
               }

               catch {
                  total += upgrade_uobj(edges[users[pos]], verbose);
               } : {
                  write(caught_error());
                  return;
               }
            } else {
               resubmit += edges[users[pos]];
            }
	 }
      }
   }

   COMPILER_D->clear_upqueue();
   rlimits(255; -1) {
      filter_array(resubmit, "resubmit_upqueue");
   }

   write("A total of " + total + " objects was upgraded.");
}

static void create() {
   set_options(([
      "help":({ ({"h", "?"}), "help" }),
      "core":({ "c", "core" }),
      "all":({ "a", "all" }),
      "verbose":({ ({ "v", "d" }), ({ "verbose", "debug" }) }),
      "file":({ "f", "file", 1, 1 })
   ]));
}

static void upgraded() {
   create();
}
