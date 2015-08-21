static mapping filter_mapping( mapping map, mixed call, varargs mixed arg... ) {
   int i, sz;
   mixed *idx;
   mapping result;

   argcheck( stringp( call ) || 
      functionp( call ), 1, "function pointer or function name" );

   result = ([ ]);
   idx = map_indices( map );

   sz = sizeof(idx);
   for (i = 0; i < sz; i++ ) {
      if (functionp( call )) {
         if ((*call)( map[idx[i]], arg... )) {
            result[idx[i]] = map[idx[i]];
         }
      } else {
         if (call_other( this_object(), call, map[idx[i]], arg... )) {
            result[idx[i]] = map[idx[i]];
         }
      }
   }

   return result;
}
