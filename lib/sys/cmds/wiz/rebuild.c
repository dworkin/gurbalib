inherit M_COMMAND;
inherit "/sys/lib/modules/m_getopt";

#ifdef SECURITY_RO_KERNEL
#define CORE_BASE "/sys/lib/auto"
#define CORE_WANTED ({ "system", "game" })
#else
#define CORE_BASE AUTO
#define CORE_WANTED ({ "kernel", "system", "game" })
#endif

string *resubmit;

string *usage(void) {
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

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "check");
   add_also("wiz", "clean");
   add_also("wiz", "clone");
   add_also("wiz", "dest");
   add_also("wiz", "eval");
   add_also("wiz", "graph");
   add_also("wiz", "update");

   add_also("admin", "checkmud");
   add_also("admin", "warmboot");
}

static int resubmit_upqueue(string f) {
   COMPILER_D->add_upqueue(f);
   return 1;
}

atomic static int upgrade_uobj(string * files, int verbose) {
   int pos, sz, uc;

   uc = 0;
   sz = sizeof(files);

   for (pos = 0; pos < sz; pos++) {
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
            error(files[pos]);
         }
      }
   }
   return uc;
}

static void main(string str) {
   int pos, sz, total, verbose, core, all;
   mapping edges;
   string *users, *wanted, *file, tmp, err;

   if (!alsos) {
      setup_alsos();
   }

   str = parse_for_options(str);
   err = query_parse_error();

   if (err) {
      write("Parse error: " + err + "\n");
      this_player()->more(usage());
      return;
   }

   if (test_option("help")) {
      this_player()->more(usage());
      return;
   }

   if (test_option("verbose")) {
      verbose = query_option("verbose");
   } else {
      verbose = 0;
   }
   core = test_option("core");
   all = test_option("all");
   file = query_option("file");

   if (!all) {
      if (core) {
         wanted = CORE_WANTED;
      } else {
         wanted = ({ });
      }

      if (str && strlen(str)) {
         wanted |= explode(str, " ");
      }

      if (!sizeof(wanted)) {
         wanted = ({ this_player()->query_name() });
      }
   } else {
      wanted = nil;
   }

   resubmit = ({ });

   if (core && (!file || !sizeof(file))) {
      file = ({ CORE_BASE });
   }

   if (verbose) {
      write("rebuild: verbose level is " + verbose);
      write("rebuild: going to perform the following actions:");

      if (file && sizeof(file)) {
         sz = sizeof(file);
         for (pos = 0; pos < sz; pos++) {
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
            users -= CORE_WANTED;
         }
         if (sizeof(users)) {
            write("rebuild all outdated objects for " + implode(users, ",") +
               ".");
         }
      }
      write("---");
   }

   if (file && sizeof(file)) {
      sz = sizeof(file);
      for (pos = 0; pos < sz; pos++) {
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

   rlimits(MAX_DEPTH; -1) {
      if (edges) {
         if (edges["kernel"] && (!wanted ||
            (sizeof(wanted & ({"kernel"})) != 0)) 
            && valid_write("/kernel/data")) {
            if (verbose > 1) {
               write("Rebuilding kernel.");
            }
            err = catch(total += upgrade_uobj(edges["kernel"], verbose));
            if (err) {
               /* upgrade_uobj will put the filename in the error string.
                  do a non-atomic, uncaught compile to show compiler errors */
               compile_object(err);
               return;
            }
            edges["kernel"] = nil;
         } else if (edges["kernel"]) {
            resubmit += edges["kernel"];
            edges["kernel"] = nil;
         }

         if (edges["system"] && (!wanted ||
            (sizeof(wanted & ({"system"})) != 0)) &&
            valid_write("/sys/data")) {

            if (verbose > 1) {
               write("Rebuilding system.");
            }

            err = catch(total += upgrade_uobj(edges["system"], verbose));
            if (err) {
               compile_object(err);
               return;
            }
            edges["system"] = nil;
         } else if (edges["system"]) {
            resubmit += edges["system"];
            edges["system"] = nil;
         }

         if (edges["game"] && (!wanted || (sizeof(wanted & ({"game"})) != 0))
            && valid_write("/daemons/data")) {
            if (verbose > 1) {
               write("Rebuilding game.");
            }
            err = catch(total += upgrade_uobj(edges["game"], verbose));
            if (err) {
               compile_object(err);
               return;
            }
            edges["game"] = nil;
         } else if (edges["game"]) {
            resubmit += edges["game"];
            edges["game"] = nil;
         }

         users = map_indices(edges);
         sz = sizeof(users);

         for (pos = 0; pos < sz; pos++) {
            if (!wanted || (sizeof(wanted & ({ users[pos] })) != 0)) {
               if (verbose > 1) {
                  write("Rebuilding for user " + users[pos]);
               }

               err = catch(total += upgrade_uobj(edges[users[pos]], verbose));
               if (err) {
                  compile_object(err);
                  return;
               }
            } else {
               resubmit += edges[users[pos]];
            }
         }
      }
   }

   COMPILER_D->clear_upqueue();
   rlimits(MAX_DEPTH; -1) {
      filter_array(resubmit, "resubmit_upqueue");
   }

   write("A total of " + total + " objects was upgraded.");
}

static void create(void) {
   mapping tmp;

   tmp = ([]);
   tmp["help"] =  ({ ({"h", "?"}), "help" });
   tmp["core"] = ({ "c", "core" });
   tmp["all"] = ({ "a", "all" });
   tmp["verbose"] = ({ ({ "v", "d" }), ({ "verbose", "debug" }), 0, 1 });
   tmp["file"] = ({ "f", "file", 1, 1 });

   set_options(tmp);
}

void upgraded(void) {
   create();
}

static int test_option_arg(string opt, string arg, int flag) {
   if (opt == "file" && arg[0] != '/') {
      return 0;
   } else {
      return ::test_option_arg(opt, arg, flag);
   }
}
