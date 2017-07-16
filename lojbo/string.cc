#ifndef __DB_TSTRING_CLASS_
#define __DB_TSTRING_CLASS_ 1

//#include <iostream>

#include "exception.cc"

class tstring {
  private:
    char *str=nullptr;
    unsigned int size=0,index=0;
    void basicalloc() {
      index=0;
      str=new char[size=4];
    }
    int resize(int n,int aesp) {
      if (n<=0 || size+n>=0xfff4) throw ALLOCOVFERR;//return 1;
      char *nstr=new char[size=((size+n)&~3)+((n&3)==0 && !aesp?0:4)];
      if (str!=nullptr) {
        strncpy(nstr,str,index);
        delete[] str;
      }
      str=nstr;
      for (unsigned int i=index;i<size;i++) str[i]='\0';
      return 0;
    }
    int compare(const char *op,unsigned int opindex) const {
      if (index!=opindex) return index-opindex;
      for (unsigned int i=0;i<index;i++) if (str[i]!=op[i]) return str[i]-op[i];
      return 0;
    }  
  public:
    tstring &operator+=(const char op) {
      if(str==nullptr) basicalloc();
      str[index++]=op;
      if(index>=size) resize(4,0);//here string cannot be nullptr
      return *this;
    }
/*  void print() const {
      if(str==nullptr) std::wcout<<std::endl;
      else {
        str[index]='\0';
        std::cout<<str<<std::endl;
      }
    }
*/
    int len() const {
      return index;
    }
    char &operator[](int i) const {
      if (i>=index) throw "index out of range";
      if (i<0) i+=index;
      if (i<0) throw "index out of range";
      return str[i];
    }
    tstring &operator+=(const tstring &op) {
      resize(op.len(),1);
      strncpy(&str[index],op.str,op.len());
      index+=op.len();
      str[index]='\0';
      return *this;
    }
    tstring &operator+=(const char *op) {
      int opl=strlen(op);
      resize(opl,1);
      strncpy(&str[index],op,opl);
      index+=opl;
      str[index]='\0';
      return *this;
    }
    tstring& operator=(const tstring& op) {
      if (this==&op) return *this;
      if (op.str==nullptr) {this->~tstring();return *this;}
      int opl=op.len();
      size=index=0;
      resize(opl,1);
      strncpy(str,op.str,index=opl);
      str[index]='\0';
      return *this;
    }
    tstring& operator=(const char *op) {
      if (op==nullptr) {this->~tstring();return *this;}
      int opl=strlen(op);
      index=size=0;
      resize(opl,1);
      strncpy(str,op,index=opl);
      str[index]='\0';
      return *this;
    }
    bool operator==(const tstring &op) const {
      return compare(op.str,op.index)==0;
    }  
    bool operator!=(const tstring &op) const {
      return compare(op.str,op.index)!=0;
    }  
    bool  operator>(const tstring &op) const {
      return compare(op.str,op.index)> 0;
    }  
    bool operator>=(const tstring &op) const {
      return compare(op.str,op.index)>=0;
    }  
    bool operator<=(const tstring &op) const {
      return compare(op.str,op.index)<=0;
    }  
    bool  operator<(const tstring &op) const {
      return compare(op.str,op.index)< 0;
    }  
    bool operator==(const char *op) const {
      return compare(op,(op!=nullptr)?strlen(op):0)==0;
    }  
    bool operator!=(const char *op) const {
      return compare(op,(op!=nullptr)?strlen(op):0)!=0;
    }  
    bool  operator>(const char *op) const {
      return compare(op,(op!=nullptr)?strlen(op):0)> 0;
    }  
    bool operator>=(const char *op) const {
      return compare(op,(op!=nullptr)?strlen(op):0)>=0;
    }  
    bool operator<=(const char *op) const {
      return compare(op,(op!=nullptr)?strlen(op):0)<=0;
    }  
    bool  operator<(const char *op) const {
      return compare(op,(op!=nullptr)?strlen(op):0)< 0;
    }    
    tstring() {}
    //size=index=0; str=nullptr;
    //}
    tstring(const char *op) {
      str=new char[size=((index=strlen(op))&~3)+4];
      strncpy(str,op,index);
    }
    tstring(const tstring &op) {
      str=new char[size=op.size];
      strncpy(str,op.str,index=op.index);
    }
    ~tstring() {
      if (str!=nullptr) {
        delete[] str;
        str=nullptr;
      }
      index=size=0;
    }
};

#endif
