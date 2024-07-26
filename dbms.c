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
		//if i use size will it change data type
		db->rows_total = db->rows_total+5;
		//if mem is null there was not enough space
		if(db->table == NULL){
			return 0;
		}
	}

	//store in rows used +1 
	//add the row 
	//need to equal row amount cause index starts from 0
	int row = db->rows_used;
	db->table[row] = *a;

	
	db->rows_used = row+1;
	db_show_row(db, row);
	return 1;
}

int db_remove_row(struct db_table *db, unsigned long id){
	//to get album 
	//for every row in the table 
	//int rows = db -> rows_used;
	int success = 0;
	int index = -1;
	//struct album *rowData = malloc(1*sizeof(struct album));
	for(unsigned int i = 0; i<db -> rows_used; i++){

		//access album id = table[1][0]??
		struct album rowData = db -> table[i];
		unsigned long albumId =  rowData.id;
		printf("%lu\n",albumId);
		//if id are equal
		if(albumId == id){
			index = i;
			success = 1;
			break;
		}
		//free(rowData);

	}

	//delete that row - do it by moving all the other ones up 

	//for all table[i] after row 
	if(index >= 0){
		for(int j = index; j<db -> rows_used; j++){
			db->table[j] = db->table[j+1];
			//make table[i] = table[i+1] - moves all up 
		}
		db -> rows_used = db -> rows_used - 1;
	}
	
			
	//records after need to be moved up 
	//if rowtotal-rowsused = 5 
	int totalRows = db -> rows_total;
	if(totalRows - (db -> rows_used) == 5){
		//free 5 rows of memory 
		
		db->table = realloc(db->table, (totalRows-5)*sizeof(struct album));
		if(db == NULL){
			return 0;
		}
		//update total 
		db -> rows_total = totalRows-5;
	}
	//update used rows 

	//if rowused = 0 (or 1 if before updating)
	if(db -> rows_used == 0){
		//free whole array 
		free(db);
		//rows = 0 
		db->rows_total;
		db->rows_used;
		//table = null
		db->table = NULL;
	}
	return success; 	
}

