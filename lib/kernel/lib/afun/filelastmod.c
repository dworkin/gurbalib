int filelastmod(string str) {
#ifdef LPC_EXT_FILELASTMOD
   return ::filelastmod(str);
#else
   return 0;
#endif
}
