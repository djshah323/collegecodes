/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _DICTIONARY_H_RPCGEN
#define _DICTIONARY_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef char *word;

struct WORD {
	word name;
	word meaning;
};
typedef struct WORD WORD;

#define DICTIONARYPROG 99
#define DICTIONARYVERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define ADDWORD 1
extern  int * addword_1(WORD *, CLIENT *);
extern  int * addword_1_svc(WORD *, struct svc_req *);
#define FINDWORD 2
extern  char ** findword_1(char **, CLIENT *);
extern  char ** findword_1_svc(char **, struct svc_req *);
#define DELETEWORD 3
extern  int * deleteword_1(char **, CLIENT *);
extern  int * deleteword_1_svc(char **, struct svc_req *);
extern int dictionaryprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define ADDWORD 1
extern  int * addword_1();
extern  int * addword_1_svc();
#define FINDWORD 2
extern  char ** findword_1();
extern  char ** findword_1_svc();
#define DELETEWORD 3
extern  int * deleteword_1();
extern  int * deleteword_1_svc();
extern int dictionaryprog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_word (XDR *, word*);
extern  bool_t xdr_WORD (XDR *, WORD*);

#else /* K&R C */
extern bool_t xdr_word ();
extern bool_t xdr_WORD ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_DICTIONARY_H_RPCGEN */
