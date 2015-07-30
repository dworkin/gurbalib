string *query_locale_data(string locale) {
#ifdef LPC_EXT_QUERY_LOCALE_DATA
   return ::query_locale_data(locale);
#else
   return nil;
#endif
}

