#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct chunk{
	struct chunk *next;
	char *value;
	size_t size;
} Chunk;

typedef Chunk *mChunk;

typedef struct chunkList {
	struct chunkList *next;
	struct chunk *headerItem;
} ChunkList;

typedef ChunkList *mChunkList;

int main() {
	char const* const fileName = {"Read3.txt"};
    FILE* file = fopen(fileName, "r");
    char line[256];
    int cnt = 0, i, listcnt = 0, cnt1 = 0;

	mChunk head = (mChunk)malloc(sizeof(Chunk));
	mChunk tail = (mChunk)malloc(sizeof(Chunk));
	mChunkList listHead = (mChunkList)malloc(sizeof(ChunkList));
	mChunkList listTail = (mChunkList)malloc(sizeof(ChunkList));
	
    while (fgets(line, sizeof(line), file)) {
        //printf("%s", line);
		cnt1++;
		mChunk newChunk = (mChunk)malloc(sizeof(Chunk));
		newChunk->next = NULL;
		newChunk->value = malloc(strlen(line) + 1 * sizeof(char));
		strcpy(newChunk->value, line);
		if(cnt == 0)
		{
			head = newChunk;
			tail = newChunk;
		}
		else
		{
			if(cnt == 1)
			{
				head->next = newChunk;
				tail = newChunk;
			}
			else
			{
				tail->next = newChunk;
				tail = newChunk;
			}
			
		}
		cnt++;
		
		if(cnt == 9216)
		{
			cnt = 0;
			mChunkList newChunkList = (mChunkList)malloc(sizeof(ChunkList));
			newChunkList->next = NULL;
			newChunkList->headerItem = head;
			if(listcnt == 0)
			{
				listHead = newChunkList;
				listTail = newChunkList;
			}
			else if(listcnt == 1)
			{
				listHead->next = newChunkList;
				listTail = newChunkList;
			}
			else
			{
				listTail->next = newChunkList;
				listTail = newChunkList;
			}
			listcnt ++;
		}
    }
    
    if(cnt != 0)
    {
    	mChunkList newChunkList = (mChunkList)malloc(sizeof(ChunkList));
		newChunkList->next = NULL;
		newChunkList->headerItem = head;
		if(listcnt == 0)
		{
			listHead = listTail = newChunkList;
		}
		else if(listcnt == 1)
		{
			listHead->next = newChunkList;
			listTail = newChunkList;
		}
		else
		{
			listTail->next = newChunkList;
			listTail = newChunkList;
		}
		while(cnt != 9216)
		{
			mChunk newChunk = (mChunk)malloc(sizeof(Chunk));
			newChunk->next = NULL;
			newChunk->value = malloc(strlen("0") + 1 * sizeof(char));
			strcpy(newChunk->value, "0\n");
			if(cnt == 0)
			{
				head = newChunk;
				tail = newChunk;
			}
			else
			{
				if(cnt == 1)
				{
					head->next = newChunk;
					tail = newChunk;
				}
				else
				{
					tail->next = newChunk;
					tail = newChunk;
				}
			}
			cnt++;
		}
		listcnt ++;
	}
        
    /***************************Function Part********************************/
    FILE *writefile = fopen("file.txt","a+"); 
	if (writefile == NULL) {
		perror("Failed to open the file");
		exit(-1);
	}
	
	while(listHead != NULL)
    {
    	head = listHead->headerItem;
		while(head != NULL)
	    {
    		fprintf(writefile,"%s",head->value);
	    	head = head->next;
		}
		
		listHead = listHead->next;
	}
	
	fclose(writefile);
    fclose(file);

    return 0;
}

