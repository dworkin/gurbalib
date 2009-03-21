#include <error_handling.h>

void rethrow() {
  string error;

  if( error = caught_error(1) ) {
    error(MAGIC_ERROR_STRING+error);
  }
} 
