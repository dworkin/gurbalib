/* reversible explode string */
static string *rexplode(string str, string sep) {
   string dummy;
   string *result;

   argcheck(stringp(str), 1, "non empty string");
   argcheck(stringp(sep), 2, "non empty string");

   if (!strlen(sep)) {
      dummy = "!";
   } else {
      if (sep[0] != '!') {
         dummy = "!";
      } else {
         dummy = "?";
      }
   }

   str = dummy + str + dummy;
   result = explode(str, sep);
   result[0] = result[0][1..];
   result[sizeof(result) - 1] =
      result[sizeof(result) - 1][..strlen(result[sizeof(result) - 1]) - 2];
   return result;
}
