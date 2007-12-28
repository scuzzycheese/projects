#ifndef HASHH
#define HASHH true

#define HASHKEYSIZE 2000

/*Linked list struct definition*/
struct hashIndex
{
	struct hashIndex *next;

	void *data;
	char *key;
};
/*just create a nice little data type that we can access */
/*easily.*/
typedef struct hashIndex **hIndex;


/*FAKE CLASSES*/

	/*CLASS hashObject*/
	/*{*/
		/*STRUCTURE*/
		struct hashObject
		{
			struct hashIndex **hashData;

			unsigned int (*hashKey)(char *, int, int);	
			void (*addIndex)(struct hashObject *, char *, int, void *);
			void (*addIndexString)(struct hashObject *, char *, void *);
			void *(*findIndex)(struct hashObject *, char *, int);
			void *(*findIndexString)(struct hashObject *, char *);
			void (*destruct)(struct hashObject *);
		};
		/*use a nice little handle*/
		typedef struct hashObject *hshObj;
	
		/*CONSTRUCTOR*/
		hshObj newHashObject();

		/*METHODS*/
		unsigned int hashKey(char *, int, int);
		void addIndex(hshObj, char *, int, void *);
		void addIndexString(hshObj, char *, void *);
		void *findIndex(hshObj, char *, int);
		void *findIndexString(hshObj, char *);
		void hashDestruct(hshObj);
	/*}*/

#endif
