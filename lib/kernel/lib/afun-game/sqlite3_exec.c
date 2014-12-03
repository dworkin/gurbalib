int *sqlite3_exec(string filename, string sql) {
#ifdef LPC_EXT_SQLITE3
	int *i;
	argcheck(filename, 1, "string");
	argcheck(sql, 2, "string");
        if (!valid_write(filename)) {
            return nil;
        }
	i = ::sqlite3_exec(filename, sql);
	return i;
#else
	return nil;
#endif
}

