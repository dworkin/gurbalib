void write(string message);

static int compile_library(string path, string code ...) {
   object ob, tmp;
   string **depends;
   int i, sz;
   mapping queue;

   argcheck(path, 1, "string");

   if (strlen(path) > 2) {
      if (path[strlen(path) - 2] == '.' && path[strlen(path) - 1] == 'c') {
         path = path[..strlen(path) - 3];
      }
   }

   if (find_object(COMPILER_D)) {
      path = COMPILER_D->allow_inherit(path, nil);
   }

   if (path) {
      tmp = ::find_object(path);
      if (tmp) {
         string **depends;
         int i, sz, ret;

         depends = COMPILER_D->find_all_depending_programs((path + "#" +
            status(tmp)[O_INDEX])) + ( { } );
         if (arrayp(depends)) {
            sz = sizeof(depends[0]);
            for (i = 0; i < sz; i++) {
               console_msg("calling compiler_d->add_upqueue()\n");
               COMPILER_D->add_upqueue(depends[0][i]);
            }
            sz = sizeof(depends[1]);
            for (i = 0; i < sz; i++) {
               COMPILER_D->add_upqueue(depends[1][i]);
            }
         }

         destruct_object(tmp);
      }
      if (code && sizeof(code)) {
         ob = driver->compile_object(path, code...);
      } else {
         ob = driver->compile_object(path);
      }

      if (ob) {
         return 1;
      }
   }
   return 0;
}
