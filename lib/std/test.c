string get_error() {
   return "woo";
}

int is_equal(mixed res, mixed res2) {
   if (res == res2) {
      return 1;
   }

   return 0;
}

/* This function trys to run cmd on the current object,
   and compares it to result.
   It will return the following values depending on what happens:
   1  = cmd == result
   0  = cmd != result
   -1 = error with cmd
 */
mixed do_test(string cmd, mixed result) {
   mixed res;

   catch {
      /* May need to do more complicated check depending on type */
      res = this_object()->call_other(cmd);
      if (is_equal(res, result)) {
         return ({1, res});
      } 
   } : {
      return ({-1, get_error()});
   }

   return ({0, dump_value(res)});
}

void do_verbose_test(string cmd, mixed result, int experror) {
   mixed ans;

   write("Calling: " + cmd + "\n");
   write("Expecting: " + dump_value(result) + "\n");

   ans = do_test(cmd, result);

   if (ans[0] == 1) {
      write("Result: Success\n");
   } else if (ans[0] == -1) {
      if (experror == 1) {
         write("Expected error: success\n");
      } else {
         write("Unexpected error: " + ans[1] + "\n");
      }
   } else {
      write("Failed, got: " + ans[1] + "\n");
   }
}
