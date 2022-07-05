#include <sqlite3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "shrd_log.h"

#define LOG_PATH "/var/log/program_logger.db"
#define TABLE_NAME "table1"

static int callback(void *, int, char **, char **);
sqlite3 *db;

int open_log() {
    char *err_msg = 0;
    int rc = sqlite3_open(LOG_PATH, &db);

    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }

    char sql[2000];

    sprintf(sql,"CREATE TABLE if NOT EXISTS %s(time TEXT, prg_name TEXT, type INT, msg TEXT);", TABLE_NAME);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);

        return 1;
    } 
    return 0;
}

int log_write(char *prg_name, int type, char *msg){

    char *err_msg = 0;
    time_t now;
    time(&now);
    char *laikas = ctime(&now);
    laikas[strcspn(laikas, "\n")] = 0;

    char sql[2000];

    sprintf(sql, "INSERT INTO %s VALUES('%s', '%s', '%d', '%s');", TABLE_NAME, laikas, prg_name, type, msg);

    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "SQL error: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);

        return 1;
    } 
    return 0;

}

void close_log() {

if(sqlite3_close(db) != SQLITE_OK){
    printf("Couldn't close database\n");
}

}


int display_log(char* log_prg_name){

    int rc;
    char *err_msg = 0;

    char sql[2000];
    if (log_prg_name == NULL) {
        sprintf(sql, "SELECT * FROM %s;", TABLE_NAME);    
    } else {
        sprintf(sql, "SELECT * FROM %s WHERE prg_name LIKE '%s'",TABLE_NAME, log_prg_name);
    }
        
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return 1;
    } 
    
    return 0;

}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {

        if((strcmp(azColName[i], "type"))==0){

            if((strcmp(argv[i],"1"))==0){
                argv[i] = "INFO";
            }

            else if((strcmp(argv[i],"2"))==0){
                argv[i] = "WARNING";
            } 

            else if((strcmp(argv[i],"3"))==0){
                argv[i] = "ERROR";
            }          

        }
        printf("%s ", argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}