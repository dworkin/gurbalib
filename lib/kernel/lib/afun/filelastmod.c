int filelastmod(string str, varargs int show_seconds_since) {
#ifdef LPC_EXT_FILELASTMOD
   return ::filelastmod(str, show_seconds_since);
#else
   return 0;
#endif
}
