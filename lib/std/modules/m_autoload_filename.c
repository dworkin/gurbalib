/* Autoload routines for use in object.c */
static string autoload_filename;

string query_autoload_filename(void) {
   return autoload_filename;
}

void set_autoload_filename(string str) {
   autoload_filename = str;
}
