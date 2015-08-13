/*
 * NAME:        call_array()
 * DESCRIPTION: call fun in all elements of the array
 * Originally created for Way of the Force by Aidil in times lost to
 * history.
 *
 * 08/2015      ported from Way of the Force by Aidil @ Way of the Force
 */
nomask static mixed *call_array(mixed *arr, string fun, varargs mixed arg...) {
   mixed *result;
   int i, sz;

   result = ({ });

   sz = sizeof(arr);
   for (i = 0; i < sz; i++ ) {
      if (!objectp( arr[i] )) {
         argcheck( 0, 1, "array of objects" );
      }
      result += ({ call_other( arr[i], fun, arg... )});
   }
   return result;
}
