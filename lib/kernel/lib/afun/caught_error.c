/*
 * Retrieve information on the last caught error
 * if flag contains something, return the entire error
 * trace, otherwise return the error (without the [CAUGHT] part)
 *
 */

string caught_error(varargs mixed flag) {
  string * lines;
  string result;

  result = DRIVER->get_tlvar(TLS_CAUGHT_ERROR);

  DRIVER->message("caught_error() : "+(result? result:"<NONE>")+"\n");

  if(!flag) {
    if(result) {
      lines = explode(result,"\n");
      sscanf(lines[0],"[CAUGHT] %s",result);
    }
  } 
  return result;
}
