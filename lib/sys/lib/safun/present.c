object present(string name, varargs mixed where...) {
   string what;
   int i, maxi, which;
   object result;

   if (sizeof(where) == 0) {
      where = ({ this_object() });
   }

   maxi = sizeof(where);
   for (i = 0; i < maxi; i++) {
   
      if (where[i]<-"/std/container") {
         if (file_exists(name)) {
            result = where[i]->find_object_filename(name);
         } else if (file_exists(name + ".c")) {
            result = where[i]->find_object_filename(name + ".c");
         } 
         else if ( sscanf(name, "%s %d", what, which) == 2 ) {
            result = where[i]->find_object_num(what, which);
            }
         else {
            result = where[i]->find_object_num(name, 1);
         }
      }
      if (result) {
         return result;
      }
   }
}
