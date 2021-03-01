// Keywords to define stringrepresentation of enumeration values

#define TYPE(type) char *valStrings##type [] = {
#define ADD(value) #value,
#define ENDTYPE(type)	\
   };							\
   typedef TDescEnum <valStrings##type, (sizeof (valStrings##type) / sizeof (char*))> TDesc##type;

// DYNAMIC ALLOCATION without deallocation, lifts 64 k boundary

// Keywords to define variable descriptors

#define VAR(type, name)				TDesc##type *pDesc##name = new TDesc##type (#name);
#define PAR(type, name, value)	TDesc##type *pDesc##name = new TDesc##type (#name);

// Keywords to define screen formatting

#define PAGE(title) TPage *pPage##title = new TPage (#title);

#define SKIP(title, rowStep, colStep)	\
   TSkip *pSkip##title = new TSkip (#title, rowStep, colStep);

/*
// STATIC OR AUTOMATIC ALLOCATION, elegant, but restricts size of PLC data to
// 64 k using BCPP compiler V1.5 and OS/2 V2.1

// Reserved words, needed to define variable descriptors

#define VAR(type, name)        TDesc##type desc##name (#name);
#define PAR(type, name, value) TDesc##type desc##name (#name);

// Reserved words, needed to define screen formatting

#define PAGE(title) TPage page##title (#title);

#define SKIP(title, rowStep, colStep)	\
   TSkip skip##title = (#title, rowStep, colStep);
*/

// Dummy keyword

#define CDEF
