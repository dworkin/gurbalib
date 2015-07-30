string query_thousands_separator(string locale) {
#ifdef LPC_EXT_QUERY_LOCALE_DATA
   return ::query_locale_data(locale)[LOCALE_THOUSANDS_SEP];
#else
   return ",";
#endif
}

