#include "graph.h"

#define _(typename, to_append) typename ## _ ## to_append
#define CALL(obj, f, args...) (obj->vtable ## . ## f)(obj, args)
#define SUPER(obj, f, args...) (obj->super, f, args)

#define NEW(type, args...) CALL((* ## type ## )malloc(sizeof( type )), init, args))


typedef struct {
	void* super;
	_(InputScanner, private_properties) private;
	_(InputScanner, vtable) vtable;
	int verticies;
} InputScanner;

typedef struct {
	_(InputScanner, private_vtable) private;
	InputScanner* (*init)(InputScanner *self);
	Graph* (*read_file)(InputScanner *self, file *f);
} _(InputScanner, vtable);

Graph* read_file(InputScanner *self, 
