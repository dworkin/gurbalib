inherit "/std/object";

int _numtests, _numsuccess, verbose;
string *_errors, *_errormsgs;
object _reporter;

void set_verbose(int x) {
   verbose = x;
}

int query_verbose() {
   return verbose;
}

string *get_errors_summary() {
   int x, maxx;
   string *res;

   maxx = sizeof(_errors);
   if (maxx > 0) {
      x = 0;
      res = ({ "\nTests: Passed: " + _numsuccess + 
         " Errors: " + maxx  + " Total Tests: " + _numtests });
      while (x < maxx) {
         res += ({ _errors[x] + " : " + _errormsgs[x] });
         x = x + 1;
      }
   } else {
     res = ({ "\nTests: Passed: " + _numtests + 
        " Errors: 0 Total Tests: " + _numtests });
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

   if (verbose) {
      while (x < maxx) {
         report_to_user(msgs[x]);
         x = x + 1;
      }
   } else {
      report_to_user(msgs[0]);
   }
}

int call_success(mixed expected, mixed result, string test_desc) {
   _numtests = _numtests + 1;
   _numsuccess = _numsuccess + 1;

   if (_reporter) {
      report_to_user(test_desc + ": Passed\n");
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

   report_to_user("\t" + test_desc + ": failed\n");

   return 0;
}

/* XXX Need to expand this */
int is_equal(mixed res, mixed res2) {
   if (res == res2) {
      return 1;
   }

   return 0;
}

/* XXX Need to catch errors as well and handle that,
   first get this working though...  */
int run_test(mixed expected, string desc, string cmd, mixed args...) {
   mixed res;
   string err;

   if (!args) {
      err = catch( res = call_other(this_object(), cmd) );
   } else {
      err = catch( res = call_other(this_object(), cmd, args) );
   }

   if (err) {
      return call_error(expected, err, desc);
   }

   if (is_equal(res, expected)) {
      return call_success(expected, res, desc);
   }
   return call_error(expected, res, desc);
}

create() {
   ::create();
   _numtests = 0;
   _numsuccess = 0;
   _errors = ({});
   _errormsgs = ({});
   _reporter = this_player();
}
