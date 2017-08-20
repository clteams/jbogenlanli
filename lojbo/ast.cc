//#include <stdlib.h>
//#include <string.h>
#include <stdarg.h>
#include "string.cc"
#include "mahoste.h"

enum astype {VALSI,OPCONN,TAGGED,INDICATOR,SUMTI,TERM/*,BRIDI,PARAGRAPH,SELBRI?*/};

class ast {
	public:
	virtual ~ast() {}
	virtual astype type() =0;
};

class indicator:public ast {
	//
	public:
	enum astype type() {return INDICATOR;}
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
		else {type=CMAVO;cm=dettype(t);}
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
	public:
	opconn(ast *c,ast *l,ast *r):conn(c),left(l),right(r) {}
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
	public:
	conn(ast *_na,ast *_se,ast *_nai,ast *_jekjoik,ast *_tag,ast *m1=NULL,ast *m2=NULL,ast *m3=NULL,ast *m4=NULL)
		:na(_na),se(_se),nai(_nai),jekjoik(_jekjoik),tag(_tag),misc1(m1),misc2(m2),misc3(m3),misc4(m4) {}
	conn *modify(ast *_nai=NULL,ast *_tag=NULL,ast *m1=NULL,ast *m2=NULL,ast *m3=NULL,ast *m4=NULL) {
			if (_nai) nai=_nai;
			if (_tag) tag=_tag;
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
	}
	conn(const ast& op) {
		//
	}
	const conn& operator=(const ast& op) {
		//
		return *this;
	}
	astype type() {return CONN;}

};

class tagged:public ast {
	ast *tag;
	ast *subtree;
	ast *misc1,*misc2;
	public:
	tagged(ast *_tag,ast *_st,ast *_m1=NULL,ast *_m2=NULL):tag(_tag),subtree(_st),misc1(_m1),misc2(_m2) {}
	~tagged() {
		//
		delete tag;
		delete subtree;
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

class term:public ast {
	ast *tag;/*(tag/FA/NA). NULL if none)*/
	ast *terminator; /*Optional KU*/
	ast *sumti;
};

class sumti:public ast {
	ast *oquant; //outer quantifier and relative clause;
	ast *orelcl;
	ast *sumti6; /*sumti6 is either description or tagged or valsi or ...*/	
};

/*
class description:public ast {
	ast *descriptor;
	ast *misc;
	ast *iquant; //inner quantifier and relative clause;
	ast *irelcl;
	ast *arg; //either sumti or selbri
};
*/

astype subteetype(ast &st) {
	switch(st.type()) {
		case TAGGED: return subtreetype(st.subtree);
		case CONN:
			astype l=subtreetype(st.left),r=subtreetype(st.right);
			//if(l!=r);
			return l;
	}
}
