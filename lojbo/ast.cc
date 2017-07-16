//#include <stdlib.h>
//#include <string.h>
#include <stdarg.h>
#include "string.cc"
#include "mahoste.h"

enum astype {VALSI,OPCONN,TAGGED};

class ast {
	public:
	virtual ~ast() {}
	virtual astype type() =0;
};

class valsi:public ast {
	enum {nobz=0,bahe=BAhE,zahe=ZAhE} emph;
	enum valsi_type {VLA,CMAVO} type;
	union {
		tstring ch;
		enum cmavo cm;
	};
	//indicators?
	public:
	valsi(const char *const bahecm,const char *const t/*indicators*/) {
		if (!strlen(bahecm)) emph=nobz; else emph=dettype(bahecm);
		if (dettype(t)==BRIVLA || dettype(t)==CMENE) {type=VLA;ch=t;}
		else {VLA=CMAVO;cm=dettype(t);}
	}
	~valsi() {}
	valsi(const ast& op) {
		//
	}
	const valsi& operator=(const valsi& op) {
		//
		return *this;
	}
	astype type() {return VALSI;}
};

class opconn:public ast {
	ast *conn;
	ast *left,*right;
	//freemodifier
	public:
	opconn(ast *c,ast *l,ast *r,ast *fm):conn(c),left(l),right(r)/*,freemod(fm)*/ {}
	~opconn() {
		//
		delete left;
		delete right;
		delete conn;
		//delete conn;
	}
	opconn(const ast& op) {
		//
	}
	const opconn& operator=(const opconn& op) {
		//
		return *this;
	}
	astype type() {return OPCONN;}
};

class conn:public ast {
	ast *na; //contains GAhO if joik is BIhI
	ast *misc1=NULL,*misc2=NULL,misc3=NULL,misc4=NULL; //contains gi if conn is forethought,also CO,BO,ZIhE,etc. 
	ast *se,*nai,*jekjoik;
	ast *tag;
	ast *freemod;
	public:
	conn(ast *_na,ast *_se,ast *_nai,ast *_jekjoik,ast *_tag,ast *fm,ast *m1=NULL,ast *m2=NULL,ast *m3=NULL,ast *m4=NULL)
		:na(_na),se(_se),nai(_nai),jekjoik(_jekjoik),tag(_tag),misc1(m1),misc2(m2),misc3(m3),misc4(m4),freemod(fm) {}
	conn *modify(ast *_nai=NULL,ast *_tag=NULL,ast *_fm,ast *m1=NULL,ast *m2=NULL,ast *m3=NULL,ast *m4=NULL) {
			if (_nai) nai=_nai;
			if (_tag) tag=_tag;
			if (_fm)  freemod=_fm;
			if (m1) misc1=m1;
			if (m2) misc2=m2;
			if (m3) misc3=m3;
			if (m4) misc4=m4;
			return this;
	}
	~conn() {
		//
		if (na) delete na;
		if (se) delete se;
		if (nai) delete nai;
		if (joikjek) delete jekjoik;
		if (tag) delete tag;
		if (misc1) delete misc1;
		if (misc2) delete misc2;
		if (freemod) delete freemod;
	}
	conn(const ast& op) {
		//
	}
	const conn& operator=(const ast& op) {
		//
		return *this;
	}
	astype type() {return CONN;}
	/*struct stagtree *stag;
	struct valsi *na,*se,*nai;
	unsigned int type;
	union {
		struct valsi *jek;
		struct valsi *joik;
	};*/

};

class tagged:public ast {
	ast *tag;
	ast *subtree;
	ast *misc1,*misc2;
	ast *freemod;
	public:
	tagged(ast *_tag,ast *_st,ast *_fm,ast *_m1=NULL,ast *_m2=NULL):tag(_tag),subtree(_st),freemod(_fm),misc1(_m1),misc2(_m2) {}
	~tagged() {
		//
		delete tag;
		delete subtree;
		//delete freemod;
	}
	tagged(const ast& op) {
		//
	}
	const tagged& operator=(const ast& op) {
		//
		return *this;
	}
	enum astype type() {return TAGGED;}
};
