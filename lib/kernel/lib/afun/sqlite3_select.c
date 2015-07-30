mixed **sqlite3_select(string filename, string sql) {
#ifdef LPC_EXT_SQLITE3_SELECT
   mixed **result_set;

   argcheck(filename, 1, "string");
   argcheck(sql, 2, "string");

   if (DAEMON() || valid_read(filename)) {
      return ::sqlite3_select(filename, sql);
   }
#endif
   return nil;
}

