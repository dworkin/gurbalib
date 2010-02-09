/*
 * Thingol, 12/02/2009
 * Split a path and return an array where the 1st member is the
 * directory, and the second member the file.
 *
 */
 
 
nomask static string *path_file(string str)
{
    string *rv;
    int i;
    
    rv = ({ "", "" });
    
    if((i = strstr(str, "/")) && i > -1)
    {
	    rv[0] = str[0..i-1];
	    
	    if(strlen(str) > i)
	    	rv[1] = str[i+1..];
    }
    
    return rv;
}
