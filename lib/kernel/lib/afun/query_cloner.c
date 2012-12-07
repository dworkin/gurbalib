string query_cloner(varargs int arg) {
   if (arg) {
      return _clone_trace;
   } else {
      return _cloner;
   }
}
