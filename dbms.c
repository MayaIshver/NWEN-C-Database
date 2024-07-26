#include <stdio.h>
#include <stdlib.h>
#include "dbms.h"



int db_show_row(const struct db_table *db, unsigned int row){
	//Allocate memory space to the row
	struct album *rowData = malloc(1*sizeof(struct album));
	if(rowData != NULL){
		//Make sure the row is within the table
		if(row<db->rows_used && row>=0){
			*rowData = db->table[row];
			/*I made the id and year into strings so that if they were 
			too long they could be truncated (i.e I can format them 
			according the brief requirements) */
			char id[100] ;
			char year[100] ;

			sprintf(id, "%lu", rowData->id);
			sprintf(year, "%d", rowData->year);

			
			printf("%6.6s:", id);
			printf("%20.20s:", rowData->title);
			printf("%20.20s:", rowData->artist);
			printf("%4.4s\n", year);
			//freeing the memory as it's no longer required
			free(rowData);
			return 1;
		}
	}
	free(rowData);
	return 0;

}

int db_add_row(struct db_table *db, struct album *a){
	
	//If all space is used add 5 memory for 5 more rows
	if(db->rows_used==db->rows_total){
		int size = db->rows_total +5;
		db->table = realloc(db->table, size*sizeof(struct album));
		//If reallocation fails, adding row has failed
		if(db->table == NULL){
			return 0;
		}
		db->rows_total = db->rows_total+5;
	}

	//Adding the row to the table
	int row = db->rows_used;
	db->table[row] = *a;

	
	db->rows_used = row+1;
	return 1;
}

int db_remove_row(struct db_table *db, unsigned long id){
	
	int success = 0;
	int index = -1;
	
	
	//Check if id is in table, if it is store that row's data 
	for(unsigned int i = 0; i<db -> rows_used; i++){
		
		unsigned long albumId = db -> table[i].id;
		if(albumId == id){
			index = i;
			success = 1;
			break;
		}
	}

	//Move the records after that row up to delete the row
	if(index >= 0){
		for(int j = index; j<db -> rows_used; j++){
			db->table[j] = db->table[j+1];
		}
		db -> rows_used = db -> rows_used - 1;
	}
			
	
	//If more than 5 rows are unused, free 5 rows of space
	int totalRows = db -> rows_total;
	if(totalRows - db -> rows_used == 5){
		db->table = realloc(db->table, (totalRows-5)*sizeof(struct album));
		if(db == NULL){
			return 0;
		}
		db -> rows_total = totalRows-5;
	}
	
	//If no rows are used, free whole table
	if(db -> rows_used == 0){
		free(db->table);
		db->table = NULL;
		//(Used and total rows have already been updated to 0, so we don't need to reset them to 0)
	}
	return success; 	
}

