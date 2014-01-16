#define MACRO_WRAP(exp) do { exp; } while(0)

#ifdef DEBUG
#define LOGGER() MACRO_WRAP(printf("Entering %s\n", __func__))
#else
#define LOGGER() MACRO_WRAP()
#endif


#ifdef VERBOSE_DEBUG
#define HANDLE(exp) MACRO_WRAP(if(exp || 1) perror(#exp);)
#else
#define HANDLE(exp) MACRO_WRAP(if(exp) perror(#exp);)
#endif
