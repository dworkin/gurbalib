/* required includes for safun's */
#include <type.h>
#include <tlsvar.h>
#include <trace.h>
#include <privileges.h>
#ifndef ENABLE_STACK_SECURITY
#define ENABLE_STACK_SECURITY
#endif

#define MODE_READ 0
#define MODE_WRITE 1


static object monster;
private object secure_d;

/* required function declarations for safun's */

int strstr(string search, string what);
object this_environment(void);
void out(string str);
void out_unmod(string str);
string pad_string_left(int len);
mixed *set_remove_repeats(mixed *a);
mixed *set_intersection(mixed *a, mixed *b, varargs int r);
mixed *set_symmetric_difference(mixed *a, mixed *b, varargs int r);
string trim_str(string str);
int str2val(string str);
nomask static int query_user_type(mixed player);
nomask int query_wizard(mixed player);
static string *rexplode(string str, string sep);

nomask int is_game_object(void) {
   return 1;
}

nomask int is_kernel_object(void) {
   return 0;
}
