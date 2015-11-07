static object new_object(object o) {
   object ob, ed;
   string trace, cloner;

   argcheck(o, 1, "object");

   ed = find_object(ERROR_D);

   /*
    * yeah.. calling the error_d to get a formatted runtime trace..
    * no, we aren't * reporting an error here, just using one of its
    * nice utility functions to get a nicely formatted trace
    */
   if (ed) {
      trace =
         ed->format_runtime_error("LWO calltrace", ::call_trace(), 0, 0, 0);
   } else {
      trace = "No LWO calltrace available\n";
   }

   cloner = previous_program();

   ob = ::new_object(o);
   ob->_F_set_cloner(cloner, trace);
   ob->_F_create();

   return ob;
}
