mixed **sqlite3_select(string filename, string sql) {
#ifdef LPC_EXT_SQLITE3
	mixed **result_set;
	argcheck(filename, 1, "string");
	argcheck(sql, 2, "string");
        if (!valid_read(filename)) {
            return nil;
        }
	result_set = ::sqlite3_select(filename, sql);
	return result_set;
#else
	return nil;
#endif
}

