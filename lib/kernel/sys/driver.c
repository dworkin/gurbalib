/*
 * Major changes by Aidil to support an external compiler_d
 * and error_d.
 *
 * Original changelog from before Gurbalib 0.41:
 *
 * Revision 1.4  1998/02/22 13:43:51  esimonse
 * Added support for editing
 *
 * Revision 1.3  1998/01/29 16:11:58  esimonse
 * Added Id and Log.
 *
 * */

#include <status.h>
#include <limits.h>
#include <ports.h>
#include <type.h>
#include <trace.h>
#include <tlsvar.h>
#include <privileges.h>
#include <error_handling.h>

#undef DEBUG_RECOMPILE

/*
 * Used by object_type(), maps between shortnames for
 * some common object types and their absolute path
 */
#define SHORT_OBJECT_TYPE ([\
  "player"     :"/sys/obj/player",\
  "user"       :"/sys/lib/user",\
  "connection" :"/kernel/obj/net/connection",\
  "port"       :"/kernel/obj/net/port",\
  "compiler"   :"/kernel/daemons/compiler_d"\
])

int tls_size, count, ocount, ident, shutting_down, boot_complete;
object compiler_d, error_d, secure_d, syslog_d, *users;

#ifdef SYS_NETWORKING
object *ports;
#endif

/* Include some useful functions from the auto object */
#include "/kernel/lib/afun/dump_value.c"
#include "/kernel/lib/afun/argcheck.c"
#include "/kernel/lib/afun/normalize_path.c"
#include "/kernel/lib/afun/require_priv.c"
#include "/kernel/lib/afun/valid.c"

void set_tls_size(int s) {
   if (KERNEL()) {
      tls_size = s + 2;
   }
}

void update_tls_size(void) {
   set_tls_size(DEFAULT_TLS_SIZE);
}

int query_tls_size(void) {
   return tls_size;
}

mixed *new_tls(void) {
   if (KERNEL()) {
      return allocate(tls_size);
   }
}

mixed get_tlvar(int i) {
   if (KERNEL()) {
      return call_trace()[1][TRACE_FIRSTARG][i + 2];
   }
}

void set_tlvar(int i, mixed v) {
   if (KERNEL()) {
      call_trace()[1][TRACE_FIRSTARG][i + 2] = v;
   }
}

void direct_message(string str) {
   send_message(str);
}

void message(string str) {
   if (syslog_d) {
      syslog_d->log_message(previous_object(), previous_program(), str);
   } else {
      direct_message(ctime(time())[4..18] + " ** " + str);
   }
}

void init_done(void) {
   if (previous_object()->base_name() == INIT_D) {
      boot_complete = 1;
   }
}

void upgrade_done(void) {
   /* a stub for now */
}

void queue_upgrade(object ob) {
   object next;
   int count;

   count = 0;

   rlimits(MAX_DEPTH; MAX_TICKS) {
      while (ob && count < 500) {
         /*
          * Note the order here, it is important.
          * doing this the other way around would result
          * in _F_upgraded() getting called immediately
          * instead of on the next call to the object/clone
          *
          */
         next = ob->next_clone();
#ifdef DEBUG_RECOMPILE
         message("call_touch " + object_name(ob) + "\n");
#endif
         call_touch(ob);
         ob = next;
         count++;
      }
   }

   if (ob) {
      call_out("continue_queue_upgrade", 0, ob);
   } else {
      upgrade_done();
   }
}

/* Ensure we have a TLS after the call_out */
void _continue_queue_upgrade(mixed * tls, object ob) {
   queue_upgrade(ob);
}

void continue_queue_upgrade(object ob) {
   _continue_queue_upgrade(allocate(query_tls_size()), ob);
}

/* Don't use this to compile inheritables! */
object compile_object(string path, varargs string code) {
   mixed stuff;
   object ob, auto;
   int mark;

   rlimits(MAX_DEPTH; -1) {
      ocount++;

      set_tlvar(TLS_INCLUDES, ( { "/kernel/include/std.h"}));
      set_tlvar(TLS_INHERITS, ( { }));
      set_tlvar(TLS_COMPILING, path);

      ident++;

      if (path != DRIVER && find_object(path)) {
         mark = 1;
      }

#ifdef DEBUG_BOOT
      if (path && !boot_complete) {
         message("BOOT: loading " + path + "\n");
      }
#endif

      if (compiler_d) {
         stuff = compiler_d->allow_compile(path, nil);
         if (typeof(stuff) == T_STRING) {
            path = stuff;
         } else if (typeof(stuff) == T_ARRAY) {
            code = implode(stuff, "\n") + "\n";
         }
      }

      if (code) {
         ob = ::compile_object(path, code);
      } else {
         ob = ::compile_object(path);
      }

      if (ob) {
         if (path != DRIVER && path != AUTO) {
            set_tlvar(TLS_INHERITS, 
               (({ find_object(AUTO)}) | get_tlvar(TLS_INHERITS)));
         }

         ident--;

         if (compiler_d) {
            compiler_d->register_includes(ob, get_tlvar(TLS_INCLUDES));
            compiler_d->register_inherits(ob, get_tlvar(TLS_INHERITS));
         }

         set_tlvar(TLS_INCLUDES, ({ }));
         set_tlvar(TLS_INHERITS, ({ }));
         set_tlvar(TLS_COMPILING, nil);

         if (mark) {
            queue_upgrade(ob);
         }
      }

      return ob;
   }
}

void register_compiler_d(void) {
   if (KERNEL()) {
      message("Registering compiler daemon : " +
         object_name(previous_object()) + "\n");
      compiler_d = previous_object();
   }
}

void register_error_d(void) {
   if (KERNEL()) {
      message("Registering error daemon    : " +
         object_name(previous_object()) + "\n");
      error_d = previous_object();
   }
}

void register_secure_d(void) {
   if (KERNEL()) {
      message("Registering security daemon : " +
         object_name(previous_object()) + "\n");
      secure_d = previous_object();
   }
}

/*
 *
 * auto_config.h contains a number of (un)defines
 * to allow writing code that optionally uses/supports
 * operator overloading and function pointers while remaining
 * backward compatible with earlier versions of the driver.
 * We don't use the version number for this, as that would
 * not work for hydra, rather we check if kfun.h was created
 * by the driver as an indication for operator overloading
 * support. Without it we can't detect the optional function 
 * pointer extension.
 *
 * the resulting file will be #included from std-kernel.h
 * and std-game.h and the kernel level auto object
 *
 */

static void write_auto_config(void) {
   string res, opt, *lines;
   int i, sz;

   remove_file("/kernel/include/auto_config.h.previous");
   rename_file("/kernel/include/auto_config.h",
      "/kernel/include/auto_config.h.previous");

   res = "#ifndef AUTO_CONFIG_DOT_H\n";
   res += "#define AUTO_CONFIG_DOT_H\n";

   opt = read_file("/kernel/include/kfun.h");
   if (opt && strlen(opt)) {
      lines = explode(opt, "\n");
      for (i = 0, sz = sizeof(lines); i < sz; i++) {
         if (sscanf(lines[i], "# define KF_%s\t%*s", opt) == 2) {
            switch(opt) {
               case "NEW_FUNCTION" :
                  res += "#define CLOSURES_EXTENSION\n";
                  break;
               default :
                  break;
            }
         }
      }
      res += "#define OPERATOR_OVERLOADING\n";
   } else {
      message("WARNING: operator overloading not available, please " +
         "upgrade your driver!\n");
   }
#ifndef MAX_STRING_SIZE
   res += "#define MAX_STRING_SIZE " + status()[ST_STRSIZE] + "\n";
#endif
   res += "#endif\n";
   write_file("/kernel/include/auto_config.h", res );
}

static void _initialize(mixed * tls) {
   message(status()[ST_VERSION] + " running " + LIB_NAME + " " + 
      LIB_VERSION + ".\n");
   message("Initializing...\n");

   write_auto_config();

   /*
    * Order is important.
    * The auto object caches the security daemon
    * so it must be loaded before anything else.
    */
   call_other(SECURE_D, "???");
   call_other(COMPILER_D, "???");
   call_other(ERROR_D, "???");

   message("Starting init_d\n");
   call_other(INIT_D, "???");

   message("Done.\n");
}

static initialize(void) {
   tls_size = DEFAULT_TLS_SIZE + 2;
   _initialize(allocate(query_tls_size()));
}

static void _save_game(mixed * tls) {
   users = users();
#ifdef SYS_NETWORKING
   ports = ports();
#endif

#ifdef SYS_PERSIST
   dump_state();
#endif
}

void save_game(void) {
   _save_game(allocate(query_tls_size()));
}

static void _restored(mixed * tls) {
   int i, sz;
   object p;

   message(status()[ST_VERSION] + " running " + LIB_NAME + " " + 
      LIB_VERSION + ".\n");

   shutting_down = 0;

   write_auto_config();

   if (users) {
      for (i = 0, sz = sizeof(users); i < sz; i++) {
         catch(users[i]->close(0));
      }
   }

#ifdef SYS_NETWORKING
   if (ports) {
      for (i = 0, sz = sizeof(ports); i < sz; i++) {
         ports[i]->reopen();
      }
   }
#endif

   message("State restored.\n");
}

static void restored(void) {
   _restored(allocate(query_tls_size()));
}

string path_read(string path) {
   string file, priv;

   if (!secure_d) {
      return "";
   }

   file = normalize_path(path, this_user()->query_player()->query_env("cwd"));

   priv = secure_d->query_read_priv(file);
   if (require_priv(priv)) {
      return file;
   } else {
      return "";
   }
}

string path_write(string path) {
   string file, priv;

   if (!secure_d) {
      return "";
   }

   file = normalize_path(path, this_user()->query_player()->query_env("cwd"));

   priv = secure_d->query_write_priv(file);
   if (require_priv(priv)) {
      return file;
   } else {
      return "";
   }
}

object call_object(string name) {
   object ob;

   rlimits(MAX_DEPTH; MAX_TICKS) {
      if (compiler_d) {
         name = compiler_d->allow_object(name);
      }

      if (ob = find_object(name)) {
         return ob;
      }
      ob = compile_object(name);
      return ob;
   }
}

object inherit_program(string file, string program, int priv) {
   object ob, *old_inherits;
   string code, old_compiling, *old_includes;
   mixed stuff;
   int c;

   c = count++;

   ident++;

   if (compiler_d) {
      program = compiler_d->allow_inherit(program, file);
   }

   if (!program) {
      return nil;
   }

   if (!(ob = find_object(program))) {

      old_includes = get_tlvar(TLS_INCLUDES);
      old_inherits = get_tlvar(TLS_INHERITS);
      old_compiling = get_tlvar(TLS_COMPILING);

      set_tlvar(TLS_INCLUDES, ({ "/kernel/include/std.h"}));
      set_tlvar(TLS_INHERITS, ({ }));
      set_tlvar(TLS_COMPILING, program);

      if (compiler_d) {
         stuff = compiler_d->allow_compile(program, nil);
         if (typeof(stuff) == T_STRING) {
            program = stuff;
         } else if (typeof(stuff) == T_ARRAY) {
            code = implode(stuff, "\n") + "\n";
         }
      }

      if (code) {
         ob = ::compile_object(program, code);
      } else {
         ob = ::compile_object(program);
      }

      if (get_tlvar(TLS_COMPILING) != AUTO) {
         set_tlvar(TLS_INHERITS, 
            (({ find_object(AUTO) }) | get_tlvar(TLS_INHERITS)));
      }

      if (program != DRIVER && program != AUTO) {
         set_tlvar(TLS_INHERITS, 
            (({ find_object(AUTO) }) | get_tlvar(TLS_INHERITS)));
      }

      if (compiler_d) {
         compiler_d->register_includes(ob, get_tlvar(TLS_INCLUDES));
         compiler_d->register_inherits(ob, get_tlvar(TLS_INHERITS));
      }

      set_tlvar(TLS_COMPILING, old_compiling);
      set_tlvar(TLS_INCLUDES, old_includes);
      set_tlvar(TLS_INHERITS, old_inherits);
   }

   if (ob) {
      set_tlvar(TLS_INHERITS, (get_tlvar(TLS_INHERITS) | ({ ob })));

   } else {
      error("NO OB");
   }

   ident--;
   return ob;
}

string include_file(string file, string path) {
   string res;

   if (compiler_d) {
      res = compiler_d->include_file(file, path);
   } else {
      if (path[0] != '/') {
         res = file + "/../" + path;
      } else {
         res = path;
      }
   }

   if (read_file(res)) {
      set_tlvar(TLS_INCLUDES, (get_tlvar(TLS_INCLUDES) | ({ res })));
   }
   return res;
}

void recompile(object obj) {
   object *stuff;

   stuff = get_tlvar(TLS_INHERITS);

   if (stuff) {
      stuff -= ( { obj } );
      set_tlvar(TLS_INHERITS, stuff);
   }
#ifdef DEBUG_RECOMPILE
   if (obj) {
      message("auto recompile inheritable: " + object_name(obj) + "\n");
   } else {
      message("auto recompile inheritable: <NIL>??\n");
   }
#endif
   if (obj) {
      destruct_object(obj);
   }
}

object _telnet_connect(mixed * tls, int port) {
   object connection;

   connection = TELNET_D->connection("<unknown>", port);
   return connection;
}

object telnet_connect(int port) {
   error("Telnet port should be disabled");
}

object _binary_connect(mixed * tls, int port) {
   object connection;

   connection = FTP_D->connection("<unknown>", port);
   return connection;
}

object binary_connect(int port) {
   return (port == 0) ?
           _telnet_connect(allocate(query_tls_size()), port) :
           _binary_connect(allocate(query_tls_size()), port);
}

void _interrupt(mixed * tls) {
   object p, *usrs;
   int i, sz;

   usrs = users();
   sz = sizeof(usrs);
   for (i = 0; i < sz; i++) {
      p = usrs[i]->query_player();
      if (p) {
         p->do_quit();
      } else {
         usrs[i]->_F_destruct();
      }
   }
   message("Shutting down.\n");
   shutdown();
}

void interrupt(void) {
   _interrupt(allocate(query_tls_size()));
}

void start_shutdown(void) {
   object p;
   int i, sz;

   users = users();

   sz = sizeof(users);
   for (i = 0; i < sz; i++) {
      p = users[i]->query_player();
      if (p) {
         p->do_quit();
      } else {
         users[i]->_F_destruct();
      }
   }

#ifdef SYS_PERSIST
   dump_state();
   message("State dumped.\n");
#endif
   message("Shutting down.\n");

   users = users();
#ifdef SYS_NETWORKING
   ports = ports();
#endif

   shutting_down = call_out("do_shutdown", 0);
}

static void _do_shutdown(mixed * tls) {
   if (shutting_down) {
      shutdown();
   }
}

static void do_shutdown(void) {
   _do_shutdown(allocate(query_tls_size()));
}

void compile_error(string file, int line, string err) {
   object usr, plr;
   string error;

   if (error_d) {
      error_d->compile_error(file, line, err);
      return;
   }

   error = file + ", " + (string) line + ": " + err + "\n";
   send_message(error);
   write_file("/logs/errors/compile", error);
   usr = this_user();
   if (usr) {
      if (usr->query_player()) {
         if (secure_d &&
            (secure_d->query_wizard(usr->query_player()->query_name()) == 1)) {
            usr->query_player()->write(error);
         } else {
            usr->query_player()->
               write("You have encountered a rift in reality. " +
                  "Please report it to the admins.\n");
         }
      }
   }
}

/* log a runtime error */
void runtime_error(string error, int caught, int ticks) {
   mixed **trace;
   string progname, objname, func, str;
   int i, sz, line, len;
   object player;

   if (error_d) {
      error_d->runtime_error(error, call_trace(), caught, ticks, -1);
      return;
   }

   if (caught) {
      return;
   }

   trace = call_trace();

   if ((sz = sizeof(trace) - 1) != 0) {
      for (i = 0; i < sz; i++) {
         progname = trace[i][1];
         func = trace[i][2];
         objname = trace[i][0];
         line = trace[i][3];
         if (line == 0) {
            str = "    ";
         } else {
            str = "    " + line;
            str = str[strlen(str) - 4..];
         }
         str += " " + func + " ";
         len = strlen(func);
         if (len < 17) {
            str += "                 "[len..];
         }
         str += progname;
         if (progname != objname) {
            len = strlen(progname);
            if (len < strlen(objname) && progname == objname[..len - 1]) {
               str += " (" + objname[len..] + ")";
            } else {
               str += " (" + objname + ")";
            }
         }
         send_message(str + "\n");
         if (i == 0) {
            send_message(error + "\nObject: " + objname + ", program: " +
               progname + ", line " + line + "\n");
            if (this_user()) {
               player = this_user()->query_player();
               if (player) {
                  player->write(error + "\nObject: " + objname + 
                     ", program: " + progname + ", line " + line + "\n");
               }
            }
         }
      }
   }
}

static string atomic_error(string error, int a, int t) {
   error = "(atom: " + a + ", " + t + " ticks remaining) " + error;

   return error;
}

static string object_type(string from, string obtype) {
   if (SHORT_OBJECT_TYPE[obtype]) {
      return SHORT_OBJECT_TYPE[obtype];
   } else {
      return normalize_path(obtype, from);
   }
}

int compile_rlimits(string objname) {
   if ((sscanf(objname, "/kernel/%*s") == 1) ||
      (sscanf(objname, "/daemons/%*s") == 1) ||
      (sscanf(objname, "/sys/%*s") == 1) || 
      (sscanf(objname, "/std/%*s") == 1) ||
      (objname == "/cmds/wiz/rebuild")) {
      return 1;
   } else {
      message("compile rlimits denied for " + objname + "\n");
   }
}

int runtime_rlimits(object obj, int stack, int ticks) {
   string *objname;

   objname = explode(object_name(obj), "/");
   switch (objname[0]) {
      case "kernel":
      case "sys":
      case "daemons":
         return 1;
         break;
      default:
         message("runtime rlimits denied for " + object_name(obj) + "\n");
         break;
   }
}

void remove_program(string ob, int t, int issue) {

#ifdef DEBUG_RECOMPILE
   message("Program " + ob + ", issue:" + issue + " (" + ctime(t) +
      ") is no longer referenced\n");
#endif

   if (compiler_d) {
      compiler_d->clear_inherits(ob, issue);
   }
}

/*
 * This will be called before an object that has been upgraded gets
 * called for the first time, it ensures _F_upgraded() gets called.
 * This needs wrapping in rlimits to protect against infinite recursion
 * and loops. Also, note that this_player() will not be set correctly
 * during an upgrade, this may need fixing later.
 */
static int _touch(mixed tls, object ob, string func) {
   object savep, *clones;
   int i;

#ifdef DEBUG_RECOMPILE
   message("touching " + object_name(ob) + " due to a call to " + func +
      "\n");
#endif

   rlimits(MAX_DEPTH; -1) {
      ob->_F_upgraded();
   }
}

int touch(object ob, string func) {
   return _touch(allocate(query_tls_size()), ob, func);
}

