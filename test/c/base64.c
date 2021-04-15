#include <stdio.h>
#include <string.h>
#include <stringc/base64.h>

int main() {
  const char *text =
    "Man is distinguished, not only by his reason, but by this singular passion from other animals, "
    "which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable "
    "generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
  const char *text_encoded = 
    "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz"
    "IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"
    "dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu"
    "dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
    "ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";

  const char *text_encoded2 = 
    "TWFu=IGl zIGRp c3Rp bmd1a XNoZW QsIG5v dCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlz"
    "IHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhb mltY WxzL CB3a Glja CBpc yBhI Gx1c3Qgb2Yg"
    "dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGlu"
    "dWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
    "ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3Vy=======ZS4=======";

  char *encode = base64encodes(0, 0, 0, text, 0);
  char *decode = base64decodes(0, 0, 0, text_encoded, 0);
  char *decode2 = base64decodes(0, 0, 0, text_encoded2, 0);

  int result = 0;
  if (strcmp(text, decode) != 0)
    puts("base64 decode failed"), result = 1;
  

  if (strcmp(text, decode2) != 0)
    puts("base64 decode with spaces and extra paddingfailed"), result = 1;
  

  if (strcmp(text_encoded, encode) != 0)
    puts("base64 encode failed"), result = 1;
  

  free(encode);
  free(decode);
  free(decode2);
  return result;
}