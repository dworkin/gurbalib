/* Returns random element from the given array.
   Returns nil if array is empty. */
mixed random_element( mixed *arr ) {
  if (sizeof(arr) < 1)
    return nil;

  return arr[random(sizeof(arr))];
}

