/*
 * appends an object to the tail of a list, a member
 * or the sentinel for the list must be provided.
 */
int list_append(string list, object member) {
   member = member->list_sentinel(list);
   if (member) {
      return list_insert(list, member);
   }
}
