//#include <stdlib.h>
//#include <string.h>
#include <stdarg.h>
#include "mahoste.h"
#include <vector>
#include <deque>
#include <string>

enum astype {VALSI,OPCONN,CONN,TAGGED,INDICATOR,SUMTI,TERM,OPERAND,NUMBER,LERFUSTR,LERFU,TANRU,DESCRIPTION,MODAL,TENSE,TST,OFFSET,INTERVAL,INTPROP,BRIDI,CMENE/*,PARAGRAPH?*/};

class ast {
	public:
	ast() {}
	virtual ~ast() {}
	ast(const ast &a) = delete;
	virtual ast &operator=(const ast &a) final = delete;
	virtual astype type() =0;
};

class indicator:public ast {
	//
	public:
	astype type() {return INDICATOR;}
};

/* general */

class valsi:public ast {
	//enum {nobz=0,bahe=BAhE,zahe=ZAhE} emph;
	cmavo cm;
	std::string ch;
	//indicators?
	public:
	valsi(const char *const bahecm,const char *const t/*indicators*/) {
		//if (!bahecm || !strlen(bahecm)) emph=nobz; else emph=static_cast<>(dettype(bahecm));
		cm=dettype(t);
		ch=(cm==cmavo::BRIVLA || cm==cmavo::CMENE)?t:"";
	}
	~valsi() {}
	astype type() {return VALSI;}
};

class opconn:public ast {
	ast *conn; //conn is of type conn or valsi or tagged(1 case)
	ast *left,*right;
	public:
	opconn(ast *c,ast *l,ast *r):conn(c),left(l),right(r) {}
	~opconn() {
		delete left;
		delete right;
		delete conn;
	}
	astype type() {return OPCONN;}
};

class conn:public ast {
	ast *na; //contains GAhO if joik is BIhI
	ast *se,*nai,*jekjoik;
	ast *tag;
	ast *misc1,*misc2,*misc3,*misc4; //contains gi if conn is forethought
	public:
	conn(ast *_na,ast *_se,ast *_nai,ast *_jekjoik,ast *_tag,ast *m1=nullptr,ast *m2=nullptr,ast *m3=nullptr,ast *m4=nullptr)
		:na(_na),se(_se),nai(_nai),jekjoik(_jekjoik),tag(_tag),misc1(m1),misc2(m2),misc3(m3),misc4(m4) {}
	conn *modify(ast *_nai=nullptr,ast *_tag=nullptr,ast *m1=nullptr,ast *m2=nullptr,ast *m3=nullptr,ast *m4=nullptr) {
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
		delete na;
		delete se;
		delete nai;
		delete jekjoik;
		delete tag;
		delete misc1;
		delete misc2;
		delete misc3;
		delete misc4;
	}
	astype type() {return CONN;}

};

class tagged:public ast {
	ast *tag;
	ast *subtree;
	ast *misc1,*misc2;
	public:
	tagged(ast *_tag,ast *_st,ast *_m1=nullptr,ast *_m2=nullptr):tag(_tag),subtree(_st),misc1(_m1),misc2(_m2) {}
	tagged *modify(ast *_t=nullptr,ast *_s=nullptr,ast *m1=nullptr,ast *m2=nullptr) {
			if (_t) tag=_t;
			if (_s) subtree=_s;
			if (m1) misc1=m1;
			if (m2) misc2=m2;
			return this;
	}
	~tagged() {
		delete tag;
		delete subtree;
		if (misc1) delete misc1;
		if (misc2) delete misc2;
	}
	astype type() {return TAGGED;}
};

/* //this class contains valsi(that sumti separates different clauses), which don't have semantical function, and are kept only because they may contain indicators
class miscvalsi:public ast {
	ast *subtree;
	ast *misc1;
	ast *misc2;
	miscvalsi(ast *_s,ast *_m1,ast *_m2=nullptr):subtree(_s),misc1(_m1),misc2(_m2) {}
}; */

class cmene:public ast {
	std::deque<ast *> ll;
	public:
	cmene(ast *_n) {ll.push_front(_n);}
	ast *append_front(ast *_n) {
		ll.push_front(_n);
		return this;
	}
	~cmene() {
		for(auto m : ll) delete m;
	}
	astype type() {return CMENE;}
};

/* bridi/bridi substructures */

class bridi:public ast {
	ast *selbri;
	ast *head_terms,*tail_terms;
	public:
	bridi(ast *_s,ast *_ht,ast *_tt):selbri(_s),head_terms(_ht),tail_terms(_tt) {}
	~bridi() {
		delete selbri;
		delete head_terms;
		delete tail_terms;
	}
	astype type() {return BRIDI;}
};

class term:public ast {
	ast *tag;/*(tag/FA/NA). nullptr if none)*/
	ast *sumti; /*or termset or KU*/
	public:
	term(ast *_t,ast *_s):tag(_t),sumti(_s) {}
	~term() {
		if (tag) delete tag;
		if (sumti) delete sumti;
	}
	astype type() {return TERM;}
};

class sumti:public ast {
	ast *oquant; //outer quantifier and relative clause;
	ast *orelcl;
	ast *sumti6; /*sumti6 is either description or tagged or valsi or ...*/	
	public:
	sumti (ast *s6,ast *_oq,ast *_oc):oquant(_oq),orelcl(_oc),sumti6(s6) {}
	~sumti() {
		if (oquant) delete oquant;
		if (orelcl) delete orelcl;
		if (sumti6) delete sumti6;
	}
        astype type() {return SUMTI;}
};

class description:public ast {
	ast *descriptor;
	ast *arg; //either sumti or selbri or cmene
	ast *iquant; //inner quantifier and relative clause;
	ast *irelcl;
	ast *misc1; //for optional KU 
	public:
	description(ast *_d,ast *_a,ast *_q,ast *_c,ast *m1):descriptor(_d),arg(_a),iquant(_q),irelcl(_c),misc1(m1) {}
	~description() {
		delete descriptor;
		delete misc1; //for optional KU 
		delete iquant; //inner quantifier and relative clause;
		delete irelcl;
		delete arg; //either sumti or selbri
	}
	ast *modify(ast *_d,ast *_m) {
		descriptor=_d;
		misc1=_m;
		return this;
	}
	ast *appendrc(ast *c) {
		//	
		return this;
	}
	astype type() {return DESCRIPTION;}
};

class tanru:public ast {
	ast *tanru_unit2;
	ast *linkargs;
	public:
	tanru(ast *_t,ast *_l):tanru_unit2(_t),linkargs(_l) {}
	~tanru() {
		delete tanru_unit2;
		if (linkargs) delete linkargs;
	}
	astype type() {return TANRU;}
};

/* mex */

class operand:public ast { //pseudo class containing the only subtree opconn [with operands]. That is because both mex and operands might be of class opconn, so it is wrong to consider them as tree and subtree
	ast *opconn;
	public:
	operand(ast *_c):opconn(_c) {}
	~operand() {
		delete opconn;//is never nullptr
	}
	astype type() {return OPERAND;}

};

/* numbers/lerfu */

class number:public ast {
	std::vector<ast *> ll;
	ast *misc1;
	public:
	number(ast *p,ast *m1=nullptr):misc1(m1) {ll.push_back(p);}
	ast *append(ast *l,ast *m1=nullptr) {
		if (l) ll.push_back(l);
		if (!misc1) misc1=m1;
		return this;
	}
	~number() {
		for(auto m : ll) delete m;
	}
	astype type() {return NUMBER;}
};

class lerfustr:public ast {
	std::vector<ast *> ll;
	ast *misc1;
	public:
	lerfustr(ast *p,ast *m1=nullptr):misc1(m1) {ll.push_back(p);}
	ast *append(ast *l,ast *m1=nullptr) {
		if (l) ll.push_back(l);
		if (!misc1) misc1=m1;
		return this;
	}
	~lerfustr() {
		for(auto m:ll) delete m;
	}
	astype type() {return LERFUSTR;}
};

class lerfu:public ast {
	ast *valsi; /* BY or any_word or lerfu_word or lerfu_string */
	ast *mod; /* LAU or TEI */
	ast *misc1; /* FOI / BU */
	public:
	lerfu(ast *_v,ast *_m=nullptr,ast *m1=nullptr):valsi(_v),mod(_m),misc1(m1) {}
	~lerfu() {
		if (valsi) delete valsi;
		if (mod) delete mod;
		if (misc1) delete misc1;
	}
	astype type() {return LERFU;}
};

/* modals */

class modal:public ast {
	ast *se;
	ast *bai;
	ast *nai;
	ast *ki;
	public:
	modal(ast *_s,ast *_b,ast *_n,ast *_k):se(_s),bai(_b),nai(_n),ki(_k) {}
	~modal() {
		if (se) delete se;
		if (bai) delete bai;
		if (nai) delete nai;
		if (ki) delete ki;
	}
	astype type() {return MODAL;}
};

class tense:public ast {
	ast *time;
	ast *space;
	ast *aspect;
	ast *ki; //CUhE
	public:
	tense(ast *_t,ast *_s,ast *_a,ast *_k):time(_t),space(_s),aspect(_a),ki(_k) {}
	~tense() {
		delete time;
		delete space;
		delete aspect;
		delete ki;
	}
	astype type() {return TENSE;}
};

class tst:public ast {
	ast *distance; //valsi
	ast *offset;//RA opconn //Right-associative because next modifies previous
	ast *interval;//
	ast *move_offest;//only for space tense,nullptr if time tense
	public:
	tst(ast *_d,ast *_o,ast *_i,ast *_mo=nullptr):distance(_d),offset(_o),interval(_i),move_offest(_mo) {}
	~tst() {
		delete distance;
		delete offset;
		delete interval;
		delete move_offest;
	}
	astype type() {return TST;}
};

class offset:public ast {
	ast *pu;//FAhA
	ast *nai;
	ast *zi;//VA
	ast *mohi;
	public:
	offset(ast *_p,ast *_n, ast *_z,ast *m1=nullptr):pu(_p),nai(_n),zi(_z),mohi(m1) {}
	~offset() {
		delete pu;
		delete nai;
		delete zi;
		delete mohi;
	}
	astype type() {return OFFSET;}
};

class interval:public ast {
	ast *zeha;//VEhA
	ast *pu;//FAhA
	ast *nai;
	ast *intprops;
	ast *viha;//nullptr if time interval
	public:
	interval(ast *_z,ast *_p,ast *_n,ast *_i,ast *_v=nullptr):zeha(_z),pu(_p),nai(_n),intprops(_i),viha(_v) {}
	~interval() {
		delete zeha;
		delete viha;
		delete pu;
		delete nai;
		delete intprops;
	}
	astype type() {return INTERVAL;}
};

class intprop:public ast {
	ast *property;
	ast *nai;
	ast *number;
	ast *mod=nullptr; //contains FEhE valsi or null
	public:
	intprop(ast *_p,ast *_n,ast *_num):property(_p),nai(_n),number(_num) {}
	~intprop() {
		delete mod;
		delete number;
		delete property;
		delete nai;
	}
	ast *modify(ast *_m) {
		if (!mod) mod=_m;
		return this;
	}
	astype type() {return INTPROP;}
};

/* end */

astype subtreetype(ast *st) {
	astype t;
	switch(t=st->type()) {
		case TAGGED: return subtreetype(st->subtree);
		case CONN: {
			astype l=subtreetype(st->left);
			astype r=subtreetype(st->right);
			if(l!=r);
			return l;
		}
		default: return t;
	}
}
