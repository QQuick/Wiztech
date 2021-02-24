// Keywords to declare enumeration types

#define TYPE(type) enum TBase##type {
#define ADD(value) value,

#define ENDTYPE(type)	\
   end##type				\
   };							\
   typedef enumT <TBase##type> type;

// Keywords to define variables

#define VAR(type, name)        type name;
#define PAR(type, name, value) type name;

// Dummy keywords

#define PAGE(title)
#define SKIP(title, rowStep, colStep)
#define CDEF




