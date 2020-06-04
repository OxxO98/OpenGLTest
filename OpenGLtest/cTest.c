#include <string.h>

float cTest(const char* key) {
	if (key == "up") {
		return -10.0f;
	}
	else if (key == "down") {
		return 10.0f;
	}
}