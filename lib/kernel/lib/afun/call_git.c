nomask int call_git(object thisp, string cmd, string dir, string message) {
   if (cmd == "push") {
   } else if (cmd == "pull") { 
   } else if (cmd == "status") { 
   } else if (cmd == "commit") { 
   } else {

/* XXX Need to do the work here.... */

       return 0;
   }
   return 1;
}
