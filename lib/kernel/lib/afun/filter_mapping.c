static mapping filter_mapping( mapping map, mixed call, varargs mixed arg... ) {
   int i, sz;
   mixed *idx;
   mapping result;

#ifdef CLOSURES_EXTENSION
   argcheck( stringp( call ) || 
      functionp( call ), 1, "function pointer or function name" );
#else
   argcheck( stringp( call ), 1, "string" );
#endif

   result = ([ ]);
   idx = map_indices( map );

   sz = sizeof(idx);
   for (i = 0; i < sz; i++ ) {

#ifdef CLOSURES_EXTENSION
      if (functionp( call )) {
         if ((*call)( map[idx[i]], arg... )) {
            result[idx[i]] = map[idx[i]];
         }
      } else {
#endif

         if (call_other( this_object(), call, map[idx[i]], arg... )) {
            result[idx[i]] = map[idx[i]];
         }

#ifdef CLOSURES_EXTENSION
      }
#endif

   }

   return result;
}
