/*
  CornerStone's Conversion Daemon

  This daemon has 2 functions, to_string() and to_value(), that aide
  in converting string representations of data types to an actual
  data-type specific value and vice versa.

  Originally created by Jason Cone (Qi@CornerStone)
*/


/*
  If nNoCount is 1, then the "|<number of elements>" is left out
  of the string conversion.  For example:

  For the array, ({"one","two","three",})
  and the mapping, ([1:"one",2:"two",3:"three",])
  
  if nNoCount == 1 then the resulting string would look like
    "({"one","two","three",})"   and
    "([1:"one",2:"two",3:"three",])" respectively

  if nNoCount == 0 or is not passed to the function, the resulting
  strings would look like
    "({3|"one","two","three",})"  and
    "([3|1:"one",2:"two",3:"three",])" respecively.
  This would give an accurate DGD-representation of an array/mapping.

  nNoCount should always = 1 when convert values to strings for the
  use of sending over the Intermud-3 network.
*/
void string to_string(mixed mValue, varargs int nNoCount)
{
  if(intp(mValue) || floatp(mValue))
    return (string)mValue;

  if(stringp(mValue))
    return "\"" + implode(explode(implode(explode(mValue, "\\"), "\\\\"),
      "\""), "\\\"") + "\"";

  if(arrayp(mValue))
  {
    mixed mReturnData;

    mReturnData = map_array(mValue, "to_string", this_object(), nNoCount);
    mValue = implode(mReturnData, ",");

    if(strlen(mValue))
      mValue += ",";

    if(nNoCount)
      return "({" +mValue+ "})";
    else
      return "({" +sizeof(mReturnData)+"|"+mValue+ "})";
  }

  if(mappingp(mValue))
  {
    mixed *mpKeys;
    mixed *mpValues;
    int nIndex;

    mpKeys = map_indices(mValue);
    mpValues = map_values(mValue);
    nIndex = sizeof(mpKeys);

    while(nIndex--)
      mpValues[nIndex] = to_string(mpKeys[nIndex], nNoCount) +
        ":" + to_string(mpValues[nIndex], nNoCount);

    mValue = implode(mpValues, ",");

    if(strlen(mValue))
      mValue += ",";

    if(nNoCount)
      return "([" +mValue+ "])";
    else
      return "([" +sizeof(mpValues)+"|"+mValue+ "])";
  }
}
 

static string sBuffer;
 

private mixed parse_data_string(int nNoCount)
{
  int nInt1;
  int nInt2;

  if(sscanf(sBuffer, "%d.%d%s", nInt1, nInt2, sBuffer) == 3
  || sscanf(sBuffer, "%d.%d", nInt1, nInt2) == 2)
    return (float)(nInt1 + "." + nInt2);

  if(sscanf(sBuffer, "%d%s", nInt1, sBuffer) == 2
  || sscanf(sBuffer, "%d", nInt1))
    return nInt1;

  if(sBuffer[0] == '\"')
  {
    string sReturnString;
    int nIndex;
    string sChar;
    mixed mChar;

    nIndex = 1;
    sReturnString = "";

    while((sChar = sBuffer[nIndex..nIndex]) != "\"")
    {
      if(sChar == "\\")
        mChar = sBuffer[++nIndex..nIndex];
      else
        mChar = sChar;

      sReturnString += mChar;

      ++nIndex;
    }

    sBuffer = sBuffer[nIndex + 1..];
    return sReturnString;
  }

  if(sBuffer[0..1] == "({")
  {
    mixed *mpArray;

    mpArray = ({});
    
    if(nNoCount)
      sBuffer = sBuffer[2..];
    else
      sBuffer = sBuffer[4..];

    while(sBuffer[0..1] != "})")
    {
      if(!strlen(sBuffer))
        error("Incomplete array.");

      mpArray += ({ parse_data_string(nNoCount) });
      sBuffer = sBuffer[1..];
    }

    sBuffer = sBuffer[2..];
    return mpArray;
  }

  if(sBuffer[0..1] == "([")
  {
    mapping aMap;

    aMap = ([]);

    if(nNoCount)
      sBuffer = sBuffer[2..];
    else
      sBuffer = sBuffer[4..];

    while(sBuffer[0..1] != "])")
    {
      mixed mKey;

      if(!strlen(sBuffer))
        error("Incomplete mapping.");

      mKey = parse_data_string(nNoCount);
      sBuffer = sBuffer[1..];
      aMap += ([ mKey : parse_data_string(nNoCount) ]);
      sBuffer = sBuffer[1..];
    }

    sBuffer = sBuffer[2..];
    return aMap;
  }

  error("Error decoding data string.");
}



mixed to_value(string sString, varargs int nNoCount)
{
  sBuffer = sString;
  return parse_data_string(nNoCount);
}