#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>

sqlite3* ppDb;

#define MAX_LENGTH 1024
#define FALSE 0
#define TRUE 1

typedef struct ctf{
	int id;
	char* flag;
	int solvers;
	char* main_story;
}ctf;

struct ctf ReturnCtf(int id);
int updateMainStoryById(const char* main_story, int id);
int updateFlagById(const char* flag, int id);
int openDBFile(const char* filename, const char* path);
int TableMaker();

int main(int argc, char** argv) {
	printf("DEBUG: Sqlite3 version: %s\n", sqlite3_libversion());
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
		return 1;
	}
	return 0;
	

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
		return 1;
	}
	return 0;
	

}




int openDBFile(const char* filename, const char* path) {

	char fullPath[100];

	strcpy(fullPath, path);
	strcat(fullPath, filename);
	// Example: filename=test.sql, path=/home/example/, result: filename=/home/example/test.sql

	int fileExist = access(fullPath, 0);
	int sqlite3Result = sqlite3_open(fullPath, &ppDb);
	if (sqlite3Result != SQLITE_OK) {
		ppDb = NULL;
		printf("Failed to open DB\n");
		
		return 1;
	}
	if (fileExist != 0) {
		return TableMaker();
	}
	sqlite3_open(fullPath, &ppDb); // for the possibility that its open and neither
	return 0;
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
		return 1;
	}
	return 0;
	
}


struct ctf returnCtf(int id) {
	struct ctf result;
	
	char query[MAX_LENGTH];

	sprintf(query, "SELECT flag, solvers, main_story"
		       "FROM ctfs"
		       "WHERE id = %d;", id);
	


	sqlite3_stmt* stmt;
	int rc = sqlite3_prepare_v2(ppDb, query, -1, &stmt, NULL);

	if (rc != SQLITE_OK) {
		printf("Error preparing query: %s \n", sqlite3_errmsg(ppDb));
		return result;
	}
	
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		result.id = id;
		strcpy(result.flag, (char*)(sqlite3_column_text(stmt, 0)));
		result.solvers = sqlite3_column_int(stmt, 1);
		strcpy(result.main_story, (char*)(sqlite3_column_text(stmt, 2)));
	}

	sqlite3_finalize(stmt);
	return result;
}
