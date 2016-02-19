#define ASSERT(condition, text) if (!(condition)) { Serial.print("ASSERT: "); Serial.println(text);}
#define UBound(n)               sizeof(n) / sizeof(n[0])
