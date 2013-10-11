mixed *bubblesort(mixed *arr) {
   int i, j, made_change, max;
   mixed  tmp;

   made_change = 1;

   max = sizeof(arr);
   for (i = 0; (i < max) && made_change; i++) {
      made_change = 0;

      for (j = 0; j < (max - 1); j++) {
         if (arr[j] > arr[j + 1]) {
            tmp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = tmp;
            made_change = 1;
         }
      }
   }

   return arr;
}
