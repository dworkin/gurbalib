/* Calculate jaccard similarity between 2 sets
   Returns a value in the range 0 (not similar at all) to 1 (very similar) */

nomask static float set_similarity( mixed *a1, mixed *a2 ) {
   argcheck( arrayp(a1), 1, "array" );
   argcheck( arrayp(a2), 2, "array" );

   if ( !sizeof( a2 ) ) {
      return (float) !sizeof( a1 );
   }

   return (float) sizeof( a1 & a2 ) / (float) sizeof( a1 | a2 );
}
