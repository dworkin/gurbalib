inherit "std/object";

int _numtests, _numsuccess;
string *_errors, *_errormsgs;
object _reporter;
int verbose;

create() {
        ::create();
	_numtests = 0;
        _numsuccess = 0;
	_errors = ({});
	_errormsgs = ({});
	_reporter = this_player();
}

void set_verbose(int x) {
   verbose = x;
}

int query_verbose() {
   return rebose;
}

string *get_errors_summary() {
   int x, maxx;
   string *res;

   maxx = sizeof(_errors);
   if (maxx > 0) {
      x = 0;
      res = ({ "\tTests: " + _numtests + " Passed: " + _numsuccess + 
         " Errors: " + maxx });
      while (x < maxx) {
         res += ({ _errors[x] + " : " + _errormsgs[x] });
         x = x + 1;
      }
   } else {
     res = ({ "Tests: " + _numtests + " Passed: " + _numtests + 
        " Errors: 0" });
   }

   return res;
}

void report_to_user(string str) {

   if (_reporter) {
      write(str);
   } else {
      console_msg(str);
   }
}

void print_errors_summary() {
   string *msgs;
   int x, maxx;

   msgs = get_errors_summary();
   maxx = sizeof(msgs);

   while(x < maxx) {
      report_to_user(msgs[x]);
      x = x + 1;
   }
}

int call_success(mixed expected, mixed result, string test_desc) {
   _numtests = _numtests + 1;
   _numsuccess = _numsuccess + 1;

   if (_reporter) {
      write(test_desc + ": Passed\n");
   }

   return 1;
}

int call_error(mixed expected, mixed result, string test_desc) {
   string res, exp;

   res = dump_value(result);
   exp = dump_value(expected);

   _numtests = _numtests + 1;
   _errors += ({ test_desc });
   _errormsgs += ({ "expected: " + exp + " got: " + res});

   if (_reporter) {
      write(test_desc + ": expected: " + exp + " got: " + res + "\n");
   }

   return 0;
}

/* XXX Need to expand these two functions */
string get_error() {
   return "woo";
}

int is_equal(mixed res, mixed res2) {
   if (res == res2) {
      return 1;
   }

   return 0;
}


/* XXX Need to catch errors as well and handle that,
   first get this working though...  */
int run_test(mixed expected, string desc, string cmd, mixed *args) {
   mixed res;

   res = this_object()->call_other(cmd, args);
   if (is_equal(res, expected)) {
      return call_success(expected, res, desc);
   }
   return call_error(expected, res, desc);
}


/* This function trys to run cmd on the current object,
   and compares it to result.
   It will return the following values depending on what happens:
   1  = cmd == result
   0  = cmd != result
   -1 = error with cmd
 */
mixed do_test(mixed result, string cmd, mixed *args) {
   mixed res;

   catch {
      /* May need to do more complicated check depending on type */
      res = this_object()->call_other(cmd,args);
      if (is_equal(res, result)) {
         return ({1, res});
      } 
   } : {
      return ({-1, get_error()});
   }
   return ({0, dump_value(res)});
}

void do_verbose_test(mixed result, int experror, string cmd, mixed *args) {
   mixed ans;

   write("Calling: " + cmd + "\n");
   write("Expecting: " + dump_value(result) + "\n");

   ans = do_test(result, cmd, args);

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
