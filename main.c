#include <stdio.h>
#include <sqlite3.h>

int main(int argc, char** argv) {
	printf("DEBUG: Sqlite3 version: %s", sqlite3_libversion());
	return 0;
}
