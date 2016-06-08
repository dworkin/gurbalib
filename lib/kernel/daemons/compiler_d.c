/* Gurbalib compiler daemon * by Aidil */
#ifndef __KERNEL__
#include "/kernel/include/std-kernel.h"
#endif

#include <privileges.h>
#include <tlsvar.h>
#include <status.h>

/* Uncomment this to enabling debugging */
/* #define DEBUG_COMPILER_D 1 */

#define INHERIT_DIRS ({ "std", "lib" })
#define OBJECT_DIRS ({ "obj", "mon", "npc", "vendors", "objects", \
   "monsters", "daemons", "rooms", "tmp", "cmds" })

#define DATA_FORMAT 1

mapping inh_list;       /* mapping for support of inherit_list */
mapping dep_list;       /* programs directly depending on the index of 
                           the mapping */
mapping programs;       /* all programs with their direct dependencies */
mapping includes;       /* everything that #includes the index of the mapping */
mapping increv;         /* all files included by the index of the mapping */
int data_format;
private mixed *pile;    /* pile of graph nodes, used to find edges of our 
                           inheritance graph */

mapping upqueue;        /* mapping of to be upgraded programs, 
                           ([ user:({ prog, prog ... }) ]) */

static void remove_all_included_by(string by);

#ifdef DEBUG_COMPILER_D
mapping query_inh_list(void) {
   return inh_list;
}

mapping query_dep_list(void) {
   return dep_list;
}
#endif

/*
 * Can't use ob->base_name() here, it would be
 * a call to ob, which isn't guaranteed to work
 * on inheritables, and will cause trouble with
 * objects that load another object from their
 * create function.
 */
static string fname(object ob) {
   string r;

   argcheck(ob, 1, "object");
   if (sscanf(object_name(ob), "%s#%*i", r) < 1) {
      r = object_name(ob);
   }
   return r;
}

static void create(void) {
   if (!get_list("clones")) {
      error("Your config file is out of date.\n" +
         "Please change the line reading:\n" +
         "create = \"create\"\n" +
         "to\n" +
         "create = \"_F_create\"\n" +
         "or see the net.dgd/mud.dgd example config files\n");
   }
   if (!inh_list) {
      inh_list = ([]);
   }
   if (!includes) {
      includes = ([]);
   }
   if (!increv) {
      increv = ([]);
   }
   if (!programs) {
      programs = ([]);
   }
   if (!dep_list) {
      dep_list = ([]);
   }

   data_format = DATA_FORMAT;

   DRIVER->register_compiler_d();
}

/*
 * Test components of a path to see if they occur
 * in the array provided as second argument
 */
private int test_path(string path, string * comp) {
   string *parts;
   int i, sz;

   parts = explode(path, "/");
   sz = sizeof(parts) -1;
   for (i = 0; i < sz; i++) {
      if (sizeof(parts[i..i] & comp) > 0) {
         return 1;
      }
   }
   return 0;
}

/* Is path a valid inheritable? */
int test_inheritable(string path) {
   return test_path(path, INHERIT_DIRS);
}

/* Is path a valid object? */
int test_object(string path) {
   return ((path == DRIVER) || test_path(path, OBJECT_DIRS));
}

/*
 * Called from the driver object before including a file.
 * It either returns a string with the path to the include
 * file (possibly translated) or an array of strings making
 * up the content of the requested file
 *
 */
mixed include_file(string file, string path) {
   if (path == "AUTO") {
      string compiling, *parts;

      compiling = DRIVER->get_tlvar(TLS_COMPILING);
      parts = explode(compiling, "/");

      if (parts[0] == "kernel") {
         /* Don't do anything for auto objects */
         if (sscanf(compiling, "/kernel/lib/auto%*s") == 0) {
            return "/kernel/include/std-kernel.h";
         }
      } else {
         if (compiling != "/sys/lib/auto") {
            return "/kernel/include/std-game.h";
         }
      }
   }

   if (path[0] != '/') {
      return file + "/../" + path;
   } else {
      return path;
   }
}

/* Include and inheritance tracking */

/* Register the compiled object for a program */
void register_program(object ob) {
   argcheck(ob, 1, "object");
   programs[object_name(ob)] = ob;
}

/* Number of programs known to the system */
int query_program_count(void) {
   if (programs) {
      return map_sizeof(programs);
   }
   return 0;
}

/* Clear inherit list for the file + issue */
void clear_inherits(string file, int issue) {
   string progname;

   argcheck(stringp(file), 1, "string");

   if (previous_program() != DRIVER) {
      error("Bad call to clear_inherits");
   }
#ifdef DEBUG_COMPILER_D
   console_msg("Clearing inherits for " + file + "#" + issue + "\n");
#endif

   if (strlen(file) > 2 && file[strlen(file) - 2..] == ".c") {
      file = file[..strlen(file) - 3];
   }

   progname = file + "#" + issue;

   remove_all_included_by(progname);

   if (inh_list[progname]) {
      int c, max;
      string *inh;
      inh = inh_list[progname];

      max = sizeof(inh);
      for (c = 0; c < max; c++) {
         if (dep_list[inh[c]]) {
            dep_list[inh[c]] -= ( { progname } );
         }
      }
      inh_list[progname] = nil;
   }

   if (dep_list[progname]) {
      string *dep;
      int c, max;

      dep = dep_list[progname];
      max = sizeof(dep);
      for (c = 0; c < max; c++) {
         if (inh_list[dep[c]]) {
            inh_list[dep[c]] -= ( { progname } );
            if (sizeof(inh_list[dep[c]]) == 0) {
               inh_list[dep[c]] = nil;
            }
         }
      }
      dep_list[progname] = nil;
   }
}

/* Register inherits for the object */
static void set_inherits(object ob, object * inherits) {
   int count, issue, obissue, sz;
   string iname, file;

   if (!objectp(ob)) {
      error("ob is not an object! " + typeof(ob));
   }

   if (file == AUTO && sizeof(inherits) != 0) {
      error("AUTO cannot have inherits!!");
   }

   file = fname(ob) + "#" + status(ob)[O_INDEX];

   if (inherits == nil) {
      inh_list[file] = nil;
      return;
   }

   inh_list[file] = ( { } );
   sz = sizeof(inherits);
   for (count = 0; count < sz; count++) {
      if (!inherits[count]) {
         error("Empty filename in set_inherits, pos is " + count);
      }

      if (fname(inherits[count]) == COMPILER_D) {
         continue;
      }
      iname = fname(inherits[count]) + "#" + status(inherits[count])[O_INDEX];
      inh_list[file] |= ({ iname });
      if (!dep_list[iname]) {
         dep_list[iname] = ({ file });
      } else {
         dep_list[iname] |= ({ file });
      }
   }
}

/* Which files inherit the argument ? */
string *inherits_this(string f, varargs int issue) {
   string *files, *result;
   int fcount, icount, max;

   result = ({ });

   files = map_indices(dep_list);

   if (!f) {
      return files;
   }

   if (issue) {
      /* We know the issue, so a simple map lookup will work */
      f += "#" + issue;
      if (dep_list[f]) {
         return dep_list[f][..];
      }
      return ({ });
      
   } else {
      /* We don't know the issue, so have to go through the keys
         and sscanf them to find all issues */
      f += "#%*d";
      rlimits(MAX_DEPTH; -1) {
         max = sizeof(files);
         for (fcount = 0; fcount < max; fcount++) {
            if (sscanf(files[fcount], f) == 1) {
               if (dep_list[files[fcount]]) {
                  return dep_list[files[fcount]][..];
               }
               return ({ });
            }
         }
      }
   }
   return ({ });
}

/*
 * Get all inheritables and objects that directly
 * inherit the inheritable provided as argument
 */
static string *get_nodes(string file) {
   int i;
   string f, *nodes;

   if (sscanf(file, "%s#%d", f, i) != 2) {
      f = file;
   }

   nodes = inherits_this(f, i);
   return nodes;
}

/*
 * Filter function for depending_objects.
 * takes the first item from the pile and checks if
 * it is an edge. If so, it is returned. If not,
 * its depends are added to the pile.
 */
static string filter_for_edges(string * nodes) {
   string node, *tmp;

   node = pile[0];
   if (!stringp(node) || sizeof(({node}) & nodes) > 0) {
      return nil;
   }
   tmp = get_nodes(node);
   if (tmp && sizeof(tmp) > 0) {
      pile += tmp;
   } else if (!test_inheritable(node) || !dep_list[node] ||
      !sizeof(dep_list[node])) {
      return node;
   }
}

/*
 * Find all objects (not inheritables) that depend on the
 * inheritable provided as argument.
 */
string *find_depending_objects(string file) {
   string newedge, *edges;

   if (strlen(file) > 2 && file[strlen(file) - 2..] == ".c") {
      file = file[..strlen(file) - 3];
   }

   edges = ({ });
   pile = get_nodes(file);

   rlimits(MAX_DEPTH; -1) {
      while (sizeof(pile)) {
         newedge = filter_for_edges(edges);

         if (newedge) {
            edges += ({ newedge });
         }

         pile -= ({ pile[0] });
      }
   }

   return map_array(edges, "issue_to_file", this_object());
}

/* Return the filename for this issue */
string issue_to_file(string str) {
   string f;

   if (sscanf(str, "%s#%*d", f) == 2) {
      return f + ".c";
   } else {
      return str;
   }
}

/* Find all inheritables that have more then one instance registered. */
mapping find_duplicates(void) {
   int i, max, dupesize;
   string *pnames, *dupes;
   mapping seen, result;

   seen = ([ ]);
   dupes = ({ });
   pnames = map_indices(inh_list);
   max = sizeof(pnames);
   for (i = 0; i < max; i++) {
      string pn;
      int issue;

      sscanf(pnames[i], "%s#%d", pn, issue);
      if (!seen[pn]) {
         seen[pn] = ({ });
      } else {
         dupes += ({ pn });
      }
      seen[pn] += ({ pnames[i] });
   }
   result = ([ ]);
   dupesize = sizeof(dupes);
   for (i = 0; i < dupesize; i++) {
      result[dupes[i]] = seen[dupes[i]];
   }
   return result;
}

/*
 * register 'inc' as a file included by 'by'.
 * Note, 'by' is an instance, not a filename
 */
static void register_included_by_single(string inc, string by) {
   if (!includes) {
      includes = ([ ]);
   }

   if (!includes[inc]) {
      includes[inc] = ({ });
   }
   includes[inc] |= ({ by });
   if (!increv[by]) {
      increv[by] = ({ });
   }
   increv[by] |= ({ inc });
}

/* Register 'list' as files included by 'what' */
void register_included_by(string what, string * list) {
   int i, max;

   if (!list) {
      return;
   }

   increv = ([ ]);
   includes = ([ ]);

   max = sizeof(list);
   for (i = 0; i < max; i++) {
      register_included_by_single(list[i], what);
   }
}

/* Unregister 'by' from all files that it includes */
static void remove_all_included_by(string by) {
   int i;
   string *stuff;

   if (arrayp(increv[by])) {
      for (i = sizeof(increv[by]) - 1; i >= 0; i--) {
         stuff = includes[increv[by][i]];
         if (stuff) {
            stuff -= ({ by });
            if (sizeof(stuff) == 0) {
               includes[increv[by][i]] = nil;
            }
         }
      }
      increv[by] = nil;
   }
}

/* Which files are included by the file provided as argument. */
string *query_includes(string what) {
   if (includes[what]) {
      return includes[what][..];
   }
}

/* Which files include the file provided as argument? */
string *query_included_by(string str) {
   if (increv[str]) {
      return increv[str][..];
   }
}

/*
 * Return an array containing two lists of programs that
 * need recompilation if the file provided in the argument
 * changed. There can be other programs depending on the
 * file, but those will be libraries that will be recompiled
 * automatically due to a parent getting recompiled.
 * This function accepts an inheritable or include file as
 * argument.
 *
 * arr[0] contains all inherits that need recompilation
 * arr[1] contains all objects that need recompilation
 *
 */
mixed *find_all_depending_programs(string file, varargs string * skip) {
   string *obs, *list, *incl, *libs;
   mixed *tmp;
   int i, max;

    /* Is this an include file? */
   list = query_includes(file);

    /* Its not, assume its a library and find the depending objects */
   if (!list) {
      return ({ ({ }), find_depending_objects(file) });
   }

   /*
    * It is an include file, find all libraries that include it directly,
    * find all objects depending on those libraries, and add any objects
    * that directly included the file.
    *
    */
   libs = ({ });
   obs = ({ });
   incl = ({ });

   if (skip) {
      list -= skip;
   } else {
      skip = ({ });
   }

   /* split the list in includes, libraries and objects */
   max = sizeof(list);
   for (i = 0; i < max; i++) {
      if (query_includes(list[i])) {
         incl |= ({ list[i] });
      } else if (test_inheritable(list[i])) {
         libs |= ({ issue_to_file(list[i]) });
         obs |= find_depending_objects(list[i]);
      } else {
         string str;

         str = issue_to_file(list[i]);
         if (find_object(str)) {
            obs |= ({ str });
         }
      }
   }

   return ({ libs[..], obs[..] });
}

void register_includes(object by, string * what) {
   if (previous_program() != DRIVER) {
      error("Bad call to register_includes");
   }

   if (what && sizeof(what)) {
#ifdef DEBUG_COMPILER_D
      console_msg(object_name(by) + " includes " + dump_value(what, ([])) + 
         "\n");
#endif
      register_included_by(object_name(by) + "#" + status(by)[O_INDEX], what);
   }
}

void register_inherits(object by, object * what) {
   if (previous_program() != DRIVER) {
      error("Bad call to register_inherits");
   }

   if (what && sizeof(what)) {
#ifdef DEBUG_COMPILER_D
      console_msg(object_name(by) + " inherits " + dump_value(what, ([])) + 
         "\n");
#endif
      set_inherits(by, what);
   }
   register_program(by);
}

mixed allow_compile(string path, string file) {
   if (!KERNEL()) {
      error("Bad call to allow_compile");
   }

   if (path == "/sys/lib/auto") {
      string *files, *code;
      int i, sz;

      code = ({ "#include \"/sys/lib/safun.c\"" });
      files = get_dir("/sys/lib/safun/*.c")[0];
      if (files) {
         for (i = 0, sz = sizeof(files); i < sz; i++) {
            code += ({ "#include \"/sys/lib/safun/" + files[i] + "\"" });
         }
      }
#ifdef DEBUG_COMPILER_D
      console_msg("Dumping safun object:\n\n" + implode(code, "\n") + "\n\n");
#endif
      return code;
   } else {
      return path;
   }
}

string allow_inherit(string path, string file) {
   if (!KERNEL()) {
      error("Bad call to allow_inherit");
   }

   if (!test_inheritable(path)) {
      error(path + " is not inheritable");
   }

   if (sscanf(path, AUTO + "%*s") != 1) {
      switch (explode(path, "/")[0]) {
         case "kernel":
            if (file && (sscanf(file, "/kernel/%*s") != 1) &&
               (sscanf(file, "/sys/%*s") != 1)) {
               error("permission denied");
            }
         case "sys":
            if ((path != "/sys/lib/auto") &&
               (sscanf(path, "/sys/lib/modules/%*s") != 1) &&
               file &&
               (owner_file(file) != "system") && 
               (owner_file(file) != "kernel")) {
               return nil;
            }
            break;

         default:
            break;
      }
   }
   return path;
}

string allow_object(string path) {
   if (test_inheritable(path) || !test_object(path)) {
      error(path + " is not an object");
   }
   return path;
}

void add_upqueue(string file) {
   string owner;

   if (!ROOT()) {
      error("Bad call to add_upqueue");
   }

   if (!upqueue) {
      upqueue = ([]);
   }
#ifdef DEBUG_COMPILER_D
   console_msg("add_upqueue: " + file + "\n");
#endif

   owner = owner_file(file);
   if (!upqueue[owner]) {
      upqueue[owner] = ({ file });
   } else {
      upqueue[owner] |= ({ file });
   }
#ifdef DEBUG_COMPILER_D
   console_msg("add_upqueue: " + "owner: " + owner + ", size: " +
      sizeof(upqueue[owner]) + "\n");
#endif
}

mapping query_upqueue(void) {
   return upqueue;
}

void clear_upqueue(void) {
   switch (owner_file(previous_program())) {
      case "kernel":
      case "system":
      case "root":
         upqueue = nil;
         break;
      default:
         error("Bad call to clear_upqueue");
   }
}

static void clean_includes(void) {
   if (data_format != DATA_FORMAT) {
      data_format = DATA_FORMAT;
      increv = ([ ]);
      includes = ([ ]);
   }
}

void upgraded(void) {
   clean_includes();
}

void rebuild_depending(string str) {
   string on, *stuff;
   int i, sz;

   stuff = find_depending_objects(str);

   if (stuff) {
      rlimits(MAX_DEPTH; -1) {
         sz = sizeof(stuff);
         for (i = 0; i < sz; i++) {
            sscanf(stuff[i], "%s.c", on);
            if (file_exists(stuff[i]) && find_object(on)) {
               compile_object(on);
            }
         }
      }
   }
}

void remove_library(string file) {
   object ob;

   ob = find_object(file, 1);

   if (ob) {
      destruct_object(ob);
   }
}
