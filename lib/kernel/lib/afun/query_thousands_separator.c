string query_thousands_separator(string locale) {
#ifdef LPC_EXT_QUERY_THOUSANDS_SEPARATOR
	return ::query_thousands_separator(locale);
#else
	return ",";
#endif
}

