int *sqlite3_exec(string filename, string sql) {
#ifdef LPC_EXT_SQLITE3_EXEC
   int *i;

   argcheck(filename, 1, "string");
   argcheck(sql, 2, "string");

   if (!valid_read(filename) && !valid_write(filename)) {
      return nil;
   }

   i = ::sqlite3_exec(filename, sql);
   return i;

#endif

   return nil;
}

