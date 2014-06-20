#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef enum _ParseState {
	FIRST_NAME,
	LAST_NAME,
	SCORE1,
	SCORE2,
	SCORE3,
	SCORE4,
	SCORE5,
	PARSE_DONE
} ParseState;

typedef struct _String {
	char *buffer;
	int length;
	int capacity;
} String;

typedef struct _Array {
	void **buffer;
	int length;
	int capacity;
} Array;

typedef struct _Record {
	String* firstName;
	String* lastName;
	int average;
	char letterGrade[3];
	int scores[5];
} Record;

String*
newString(int capacity) {
	String* a = malloc(sizeof(String));

	a->buffer = malloc(sizeof(char) * capacity);
	a->capacity = capacity;
	a->length = 0;

	return a;
}

void
appendToString(String *a, char ch) {
	if (a->length == a->capacity) {
		a->buffer = realloc(a->buffer,
			a->capacity * sizeof(char) * 2);
		a->capacity *= 2;
	}

	a->buffer[a->length] = ch;
	a->length += 1;
}

char*
stringAsCString(String *str) {
	if (str->length == 0 || str->buffer[str->length - 1] != '\0') {
		appendToString(str, '\0');
	}

	return str->buffer;
}

void
trimString(String *str) {
	if (str->length == 0) {
		return;
	}

	int start, end;

	for (start = 0; start < str->length; ++start) {
		if (!isspace(str->buffer[start])) {
			break;
		}
	}

	for (end = str->length - 1; end >= 0; --end) {
		if (!isspace(str->buffer[end])) {
			break;
		}
	}
	//All spaces?
	if (end < 0) {
		str->length = 0;

		return;
	}
	//Trim start
	if (start > 0) {
		memmove(str->buffer, str->buffer + start, str->length - start);
	}
	//Trim end
	str->length = end  - start + 1;
}

void
deleteString(String *a) {
	free(a->buffer);
	a->buffer = NULL;
	free(a);
}

Array*
newArray(int capacity) {
	Array* a = malloc(sizeof(Array));

	a->buffer = malloc(sizeof(void*) * capacity);
	a->capacity = capacity;
	a->length = 0;

	return a;
}

void*
getArrayItem(Array *a, int index) {
	assert(index >= 0 && index < a->length);

	return a->buffer[index];
}
void*
setArrayItem(Array *a, int index, void *obj) {
	assert(index >= 0 && index < a->length);

	a->buffer[index] = obj;

	return obj;
}

void
addArrayItem(Array *a, void *obj) {
	if (a->length == a->capacity) {
		a->buffer = realloc(a->buffer,
			a->capacity * sizeof(void*) * 2);
		a->capacity *= 2;
	}

	a->buffer[a->length] = obj;
	a->length += 1;
}

void
deleteArray(Array *a) {
	free(a->buffer);
	a->buffer = NULL;
	free(a);
}

Record*
newRecord() {
	Record *rec = malloc(sizeof(Record));
	rec->firstName = newString(10);
	rec->lastName = newString(10);

	return rec;
}

void
deleteRecord(Record *rec) {
	deleteString(rec->firstName);
	deleteString(rec->lastName);

	free(rec);
}

ParseState
parseChar(FILE *file, Array *list) {
	static ParseState state = FIRST_NAME;
	static Record *record = NULL;
	int ch = fgetc(file); 

	if (ch == EOF) {
		state = PARSE_DONE;

		return state;
	}

	if (ch == '\r') {
		return state; //Eat
	}

	if (ch == '\n') {
		return state;
	}

	if (state == FIRST_NAME) {
		if (record == NULL) {
			record = newRecord();
		}
		if (ch == ',') {
			//Done with first name
			state = LAST_NAME;

			return state;
		}
		appendToString(record->firstName, ch);
	}

	if (state == LAST_NAME) {
		if (isdigit(ch)) {
			//We have hit score

			//Read the scores
			ungetc(ch, file);

			fscanf(file, "%d %d %d %d %d",
				record->scores,
				record->scores + 1,
				record->scores + 2,
				record->scores + 3,
				record->scores + 4);

			//Add record to list
			addArrayItem(list, record);
			//Start a new record
			state = FIRST_NAME;
			record = NULL;

			return state;
		} else {
			appendToString(record->lastName, ch);

			return state;
		}
	}

	return state;
}

int
recordCompare(const void* o1, const void *o2) {
	Record **r1 = (Record**) o1;
	Record **r2 = (Record**) o2;

	return ((*r2)->average - (*r1)->average);
}

int
scoreCompare(const void* o1, const void *o2) {
	int *s1 = (int*) o1;
	int *s2 = (int*) o2;

	return (*s1 - *s2);
}

void
printRecord(Record *rec) {
	printf("%s %s (%d%%) (%s): %d %d %d %d %d\n", 
		stringAsCString(rec->lastName),
		stringAsCString(rec->firstName),
		rec->average, 
		rec->letterGrade,
		rec->scores[0],
		rec->scores[1],
		rec->scores[2],
		rec->scores[3],
		rec->scores[4]);
}

void
processRecord(Record *rec) {
	trimString(rec->firstName);
	trimString(rec->lastName);

	//Calculate average score
	double avg = 1.0/5.0 * (
		rec->scores[0] +
		rec->scores[1] +
		rec->scores[2] +
		rec->scores[3] +
		rec->scores[4]
	);

	rec->average = (int) (avg + 0.5); //Round up

	//Get the letter grade for average
	int numRange[] =   {93, 90, 87, 83, 80, 77, 73, 70, 67, 63, 60, 0};
	char *letterGrade[] = {"A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D+", "D", "D-", "F"};

	for (int i = 0; i < sizeof(numRange) / sizeof(int); ++i) {
		if (rec->average >= numRange[i]) {
			strcpy(rec->letterGrade,
				letterGrade[i]);
			break;
		}
	}

	//Sort the scores
	qsort(rec->scores, sizeof(rec->scores) / sizeof(int), sizeof(int),
		scoreCompare);
}


int
main(int argc, char **argv) {
	if (argc < 2) {
		puts("Usage: main file_name");
		return 1;
	}

	FILE *file = fopen(argv[1], "r");
	assert(file != NULL);

	Array *recordList = newArray(10);

	while (parseChar(file, recordList) != PARSE_DONE) {
	}

	//Process each record
	for (int i = 0; i < recordList->length; ++i) {
		Record *rec = getArrayItem(recordList, i);
		processRecord(rec);
	}

	//Sort all the records
	qsort(recordList->buffer, recordList->length, sizeof(void*),
		recordCompare);

	for (int i = 0; i < recordList->length; ++i) {
		Record *rec = getArrayItem(recordList, i);
		printRecord(rec);
	}

	fclose(file);
}
