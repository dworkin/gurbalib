/*
 * Retrieve information on the last caught error
 * if flag contains something, return the entire error
 * trace, otherwise return the error (without the [CAUGHT] part)
 *
 */

string caught_error(varargs mixed flag) {
   string *lines;
   string result;

   result = driver->get_tlvar(TLS_CAUGHT_ERROR);

   if (!flag) {
      if (result) {
         lines = explode(result, "\n");
         result = lines[0];
      }
   }
   return result;
}
