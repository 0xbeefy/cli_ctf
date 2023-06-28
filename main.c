#include <stdio.h>
#include <sqlite3.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

sqlite3* ppDb;

#define MAX_LENGTH 1024
#define FALSE 0
#define TRUE 1
#define PATH_MAX 200
#define CLEAR printf("\e[1;1H\e[2J");

int updateMainStoryById(const char* main_story, int id);
int updateFlagById(const char* flag, int id);
int updateSolversById(int solvers, int id);
int openDBFile(const char* filename, const char* path);
int TableMaker();

int main(int argc, char** argv) {
	char newQuery[100] = {0};
	char cwd[PATH_MAX] = {0};
	char* errorMessage;
	char command[100] = {0};

	char currentFlag[100] = {0};
	char currentSolvers[100] = {0};
	char currentMainStory[300] = {0};
	char id[100] = {0};
	char flag[100] = {0};
	if (getcwd(cwd, sizeof(cwd)) == NULL) {
		printf("Error getting current working directory\n");
		return 1;
	}
	openDBFile("db.sql", cwd);
	while (1) {
		CLEAR
		printf("Input a number from the menu:\n");
		printf("1) Add new challenge\n2) Change flag of challenge (by ID)\n3) Change solvers number of challenge (by ID)\n4) Change main story of challenge (by id)\n");
		printf("CTF> ");
		fgets(command, 100, stdin);
		command[strcspn(command, "\n")] = 0;
		if ( strcmp(command, "1") == 0 ) {
			printf("Creating a new challenge.\n");
			printf("Challenge current flag (can leave blank): ");
			fgets(currentFlag, 100, stdin);
			currentFlag[strcspn(currentFlag, "\n")] = 0;
			printf("Challenge current solvers (int) (can leave blank): ");
			fgets(currentSolvers, 100, stdin);
			currentSolvers[strcspn(currentSolvers, "\n")] = 0;
			printf("Challenge current main story (can leave blank): ");
			fgets(currentMainStory, 100, stdin);
			currentMainStory[strcspn(currentMainStory, "\n")] = 0;

			sprintf(newQuery, "INSERT INTO ctfs (flag, solvers, main_story)"
					  "VALUES ('%s', %d, '%s');", currentFlag, (int) strtol(currentSolvers, (char **)NULL, 10), currentMainStory);
		} else if ( strcmp(command, "2") == 0 ) {
			printf("ID of challenge to change: ");
			fgets(id, 100, stdin);
			id[strcspn(id, "\n")] = 0;
			printf("New flag: ");
			fgets(flag, 100, stdin);
			flag[strcspn(flag, "\n")] = 0;
			updateFlagById(flag, (int) strtol(id, (char **)NULL, 10));
		}
		int rc = sqlite3_exec(ppDb, newQuery, NULL, 0, &errorMessage);
		if (rc != SQLITE_OK) {
			printf("Error preparing query: %s \n", errorMessage);
			return 1;
		}
	}
	sqlite3_close(ppDb);

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

int updateSolversById(int solvers, int id) {
	
 	char query[MAX_LENGTH];

	sprintf(query, "UPDATE ctfs "
		       "SET solvers = '%d' "
		       "WHERE id = %d; ", solvers, id);



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
	char slash = '/';

	strcpy(fullPath, path);
	strcat(fullPath, "/");
	strcat(fullPath, filename);
	printf("%s\n", fullPath);
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
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"flag TEXT,"
		"solvers INTEGER,"
		"main_story TEXT );";

	char* errorMessage;

	int rc = sqlite3_exec(ppDb, query, NULL, 0, &errorMessage);
	if (rc != SQLITE_OK) {
		printf("Error creating table: %s \n", errorMessage);
		return 1;
	}
	printf("DEBUG: Created TABLE ctfs\n");
	return 0;
	
}
