inherit "std/test";

int test_nil() {
   return intp(nil);
}

int test_intp_int(int x) {
   return intp(x);
}

int test_intp_float(float x) {
   return intp(x);
}

int test_intp_string(string x) {
   return intp(x);
}

int test_intp_obj(object x) {
   return intp(x);
}

void setup() { }

void create () {
   int x, i, *ai;
   float f, *af;
   string s, *as;
   object o, *ao;
   mapping m, *am;
   mixed mix, *amix, *args;

   ::create();

   set_id("testobject");

   args = ({});
   run_test(0, "intp(nil)", "test_nil", args);

/* XXX Throws an error 
   x = intp(void);
   write("intp(void) returns :" + x + "\n");
*/

   args = ({ 5 });
   run_test(1, "intp(5)", "test_intp_int", args);

   args = ({ 5.0 });
   run_test(1, "intp(5.0)", "test_intp_float", args);

   args = ({ 5.5 });
   run_test(1, "intp(5.5)", "test_intp_float", args);

   args = ({ i });
   run_test(1, "int i; intp(i); /*uninitalized int */",
	"test_intp_int", args);

   i = 5;
   args = ({ i });
   run_test(1, "int i; i = 5; intp(i);", "test_intp_int", args);

   args = ({ f });
   run_test(1, "float f; intp(f); /*uninitalized float */",
	"test_intp_float", args);

   f = 5.0; 
   args = ({ f });
   run_test(1, "float f; f = 5.0; intp(f);", "test_intp_float", args);

   args = ({ s });
   run_test(1, "string s; intp(s);", "test_intp_string", args);

   s = "5";
   args = ({ s });
   run_test(1, "string s; s = \"5\"; intp(s);", "test_intp_string", args);

   args = ({ o });
   run_test(1, "object o; intp(o);", "test_intp_obj", args);

   o = this_object();
   args = ({ o });
   run_test(1, "object o; o = this_object; intp(o);", "test_intp_obj", args);

/* XXX Here */
   x = intp(m);
   write("intp(m) returns: " + x + "\n");

   m = ([]);
   x = intp(m);
   write("m = ([]); intp(m) returns: " + x + "\n");

   m = ([]);
   m[1] = 5;
   x = intp(m);
   write("m = ([]); m[1] = 5; intp(m) returns: " + x + "\n");

   x = intp(m[1]);
   write("m = ([]); m[1] = 5; intp(m[1]) returns: " + x + "\n");

   x = intp(ai);
   write("intp(ai) returns: " + x + "\n");

   ai = ({ 1 });
   x = intp(ai[0]);
   write("intp(ai[0]) returns: " + x + "\n");

/* XXX Need more tests have to test all array stuff here */
   x = intp(af);
   write("intp(af) returns: " + x + "\n");
   print_errors_summary();
}

