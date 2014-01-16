#include <assert.h>

#define CALL_PRIVATE(obj, f, args...) (obj->vtable.private_vtable. ## f)(obj, args)
#define SET_PRIVATE(obj, prop, val) obj->private. ## prop = val
#define GET_PRIVATE(obj, prop) obj->private. ## prop 

#define MAX_SIZE 300

typedef struct {
	int width;
	int height;
	int max_dist;
	int inf_dist;
} _(InputScanner, private_properties);

typedef struct {
	int* (*read_line)(InputScanner *self, file *f);
} _(InputScanner, private_vtable);

/* Function prototype here so we can define DEFAULT_PRIVATE_VTABLE */
int* _(InputScanner, read_line)(InputScanner *self, file *f);

const _(InputScanner, private_properties) DEFAULT_PRIVATE_PROPERTIES = {
	.width = 0,
	.height = 0,
	.max_dist = 0,
	.inf_dist = 0
};

const _(InputScanner, private_vtable) DEFAULT_PRIVATE_VTABLE = {
	.read_line = & _(InputScanner, read_line)
};
	

InputScanner* _(InputScanner, init)(InputScanner *self){
	self->super = NULL; 		/* not inheriting from anything */
	self->vtable = INPUTSCANNER_VTABLE;
	self->vtable.private = DEFAULT_PRIVATE_VTABLE;
	self->private = DEFAULT_PRIVATE_PROPERTIES;

	self->verticies = 0;
	
	return self;
}

Graph* _(InputScanner, read_file)(InputScanner *self, file *f){
	int num_read;

	int height = 0;	 
	int *rv[MAX_SIZE] = {NULL}
	
	int old_verticies = self->verticies;
	
	while(rv[height++] = CALL_PRIVATE(self, read_line, f, num_read)){
		if(num_read > self.verticies){
			self->verticies = num_read;
		}
	}
	
	SET_PRIVATE(self, height, (height));
	
	assert(self->verticies == GET_PRIVATE(self, height) == GET_PRIVATE(self, width));
}

int* _(InputScanner, read_line)(InputScanner *self, file *f){
	int *rv;
	int width;
	char line[MAX_SIZE];

	
	if(!fgets(line, MAX_SIZE, f)){
		rv = NULL;
	}
	

