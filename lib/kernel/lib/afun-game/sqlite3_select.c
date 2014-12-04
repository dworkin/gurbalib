mixed **sqlite3_select(string filename, string sql) {
#ifdef LPC_EXT_SQLITE3
	mixed **result_set;
	argcheck(filename, 1, "string");
	argcheck(sql, 2, "string");
	return ::sqlite3_select(filename, sql);
#else
	return nil;
#endif
}

