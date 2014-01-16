#define ASSERT(exn) assert(exn); printf("%s (%i): PASS\n", #exn, __LINE__)
#define BIG_SEP() printf("---------------\n")
#define SMALL_SEP() printf("* * * * * * * *\n")
#define DONE() printf("All tests passed!\n")
