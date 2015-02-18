int blog_it(string title, string content, string author) {

#ifdef LPC_EXT_BLOG_IT
   if (strlen(title) > 255) {
      return -1;
   }
   if (strlen(content) > 1023) {
      return -2;
   }
   if (strlen(author) > 11) {
      return -3;
   }

   return ::blog_it(title, content, author);
#else
   return 0;
#endif
}

