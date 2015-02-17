/*
 * Thingol, 12/02/2009
 * Split a path and return an array where the 1st member is the
 * directory, and the second member the file.
 */

nomask static string *path_file(string str) {
   string *arr;

   arr = rexplode(str, "/");

   return ( { implode(arr[..sizeof(arr) - 2], "/"), arr[sizeof(arr) - 1] } );
}
