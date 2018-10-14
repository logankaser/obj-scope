#include <stdio.h>
#include "scop.h"

EMSCRIPTEN_KEEPALIVE
void	load_obj_from_js(const uint8_t *buff, size_t size)
{
	FILE *tmp;

	tmp = tmpfile();
	fwrite(buff, 1, size, tmp);

    char* line = NULL;
    size_t n = 0;
    ssize_t read;
    while ((read = getline(&line, &n, tmp)) > 0) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        line = NULL;
    }
	obj_open(tmp);
	fclose(tmp);
}