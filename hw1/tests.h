#pragma once

#define ASSERT(exn) assert((exn)b); printf("%s (%i): PASS\n", #exn, __LINE__)
#define BIG_SEP() printf("---------------\n")
#define SMALL_SEP() printf("* * * * * * * *\n")
#define DONE() printf("All tests passed!\n")
