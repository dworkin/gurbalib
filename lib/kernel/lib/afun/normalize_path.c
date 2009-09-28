/*
 * NAME:        normalize_path()
 * DESCRIPTION: reduce a path to its minimal absolute form
 */
string normalize_path(string file, string dir)
{
  string *path;
  int i, j, sz;

  argcheck( file, 1, "string" );
  argcheck( dir, 2, "string" );

  if(!secure_d) secure_d = ::find_object(SECURE_D);

  if (strlen(file) == 0) {
    file = dir;
  }
  switch (file[0]) {
  case '~':
    /* ~path */
    if(strlen(file) == 1 || file[1] == '/') {
      file = WIZ_DIR + this_user()->query_user()->query_name() + file[1 ..];
    } else {
      file = WIZ_DIR + file[1 ..];
    }
    /* fall through */
  case '/':
    /* absolute path */

    path = explode(file, "/");

/*
    if( (path[0] == "data" || path[0] == "kernel") && !secure_d->query_admin( this_user()->query_name() ) )
      return("");
*/

    if (sscanf(file, "%*s//") == 0 && sscanf(file, "%*s/.") == 0) {
      return file;      /* no changes */
    }
    break;

  default:
    /* relative path */
    if (sscanf(file, "%*s//") == 0 && sscanf(file, "%*s/.") == 0 &&
        sscanf(dir, "%*s/..") == 0) {
      /*
       * simple relative path
       */

      if( dir[strlen(dir)-1] == '/' )
        path = explode( dir + file, "/" );
      else
        path = explode( dir + "/" + file, "/" );

/*
      if( (path[0] == "data" || path[0] == "kernel") && !secure_d->query_admin( this_user()->query_name() ) )
        return("");
*/


      if( dir[strlen(dir)-1] == '/' )
        return dir + file;
      else
        return dir + "/" + file;
    }
    /* fall through */
  case '.':
    /*
     * complex relative path
     */
    path = explode(dir + "/" + file, "/");
    break;
  }

  for (i = 0, j = -1, sz = sizeof(path); i < sz; i++) {
    switch (path[i]) {
    case "..":
      if (j >= 0) {
        --j;
      }
      /* fall through */
    case "":
    case ".":
      continue;
    }
    path[++j] = path[i];
  }

/*
  if( (path[0] == "data" || path[0] == "kernel") && !secure_d->query_admin( this_user()->query_name() ) ) {
    return "";
  }
*/

  return "/" + implode(path[.. j], "/");
}

