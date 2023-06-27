#include <stdio.h>
#include <sqlite3.h>

sqlite3* ppDb;

#define MAX_LENGTH 1024
#define FALSE 0
#define TRUE 1

int updateMainStoryById(const char* main_story, int id);
int updateFlagById(const char* flag, int id);
int openDBFile(const char* filename, const char* path);
int TableMaker();

int main(int argc, char** argv) {
	printf("DEBUG: Sqlite3 version: %s", sqlite3_libversion());
	return 0;
}

int updateFlagById(const char* flag, int id){
	
 	char query[MAX_LENGTH];
    sprintf(query, "UPDATE ctfs "
                   "SET flag = '%s' "
                   "WHERE id = %d; ", flag, id);



	char* errorMessage;

	int rc = sqlite3_exec(ppDb, query, NULL, 0, &errorMessage);
	if (rc != SQLITE_OK) {
		printf("Error preparing query: %s \n", errorMessage);
		return FALSE;
	}
	return TRUE;
	

}

int updateMainStoryById(const char* main_story, int id){
	
 	char query[MAX_LENGTH];

    sprintf(query, "UPDATE ctfs "
                   "SET main_story = '%s' "
                   "WHERE id = %d; ", main_story, id);



	char* errorMessage;

	int rc = sqlite3_exec(ppDb, query, NULL, 0, &errorMessage);
	if (rc != SQLITE_OK) {
		printf("Error preparing query: %s \n", errorMessage);
		return FALSE;
	}
	return TRUE;
	

}




int openDBFile(const char* filename, const char* path) {

	char fullPath[100];

	strcpy(fullPath, path);
	strcat(fullPath, filename);

	int fileExist = _access(fullPath, 0);
	int sqlite3Result = sqlite3_open(fullPath, &ppDb);
	if (sqlite3Result != SQLITE_OK) {
		ppDb = NULL;
		printf("Failed to open DB\n");
		
		return FALSE;
	}
	if (fileExist != 0) {
		return TableMaker();
	}
	sqlite3_open(fullPath, &ppDb); // for the possibility that its open and neither
}

int TableMaker(){
	const char* query = 
		"CREATE TABLE IF NOT EXISTS ctfs ("
		"id INTEGER AUTOINCREMENT ,"
		"flag TEXT,"
		"solvers INTEGER,"
		"main_story TEXT );";

	char* errorMessage;

	int rc = sqlite3_exec(ppDb, query, NULL, 0, &errorMessage);
	if (rc != SQLITE_OK) {
		printf("Error creating table: %s \n", errorMessage);
		return FALSE;
	}
	return TRUE;
	
}