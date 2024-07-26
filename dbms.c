#include <stdio.h>
#include <stdlib.h>
#include "dbms.h"



/**
 * Function prototype for Task 1. See handout for details.
 */ 
int db_show_row(const struct db_table *db, unsigned int row){
	//to store the row of data and allocate size/space
	struct album *rowData = malloc(1*sizeof(struct album));
	if(rowData != NULL){//making sure we have space 
		if(row<db->rows_used){//make sure the row is in the table
			*rowData = db->table[row];
			//make row = the row data 
			//struct album *rowData = *db[row];

			//if table has row
			//print and return 1 
			//else return 0
			//print
			printf("%6d:",rowData->id);
			printf("%20.20s:", rowData->title);
			printf("%20.20s:", rowData->artist);
			printf("%d\n", rowData->year);
			return 1;
		}
	}
	return 0;
}

int db_add_row(struct db_table *db, struct album *a){
	
	//has to be space
	if(db->rows_used==db->rows_total){
		//if all space is used
		int size = db->rows_total +5;
		//reallocate mem (add 5)
		db->table = realloc(db->table, size*sizeof(struct album));
		//if mem is null there was not enough space
		if(db->table == NULL){
			return 0;
		}
	}

	//store in rows used +1 
	//add the row 
	int row = db->rows_used;
	db->table[row] = *a;
	db->rows_used = row+1;
	return 1;
}



