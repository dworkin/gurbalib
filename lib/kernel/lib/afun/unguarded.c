static mixed unguarded(mixed fun, varargs mixed args ...) { 

#ifndef CLOSURES_EXTENSION 
   argcheck( stringp(fun), 1, "string" ); 
#else 
   argcheck( stringp(fun) || functionp(fun), 1, "string or function pointer"); 

   if (stringp(fun)) { 
#endif 
      if (!function_object(fun, this_object())) { 
         error("Undefined function: " + fun); 
      } 

      return call_other(this_object(), fun, args...); 
#ifdef CLOSURES_EXTENSION 
   } else { 
      return (*fun)(args...); 
   } 
#endif 
} 
