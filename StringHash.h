#ifndef __STRING_HASH__
#define __STRING_HASH__

#include <string>
using namespace std;

#define MAXTABLELEN 1024    
//////////////////////////////////////////////////////////////////////////  
 
typedef struct  _HASHTABLE
{  
  	long nHashA;  
	long nHashB;  
	bool bExists;  
}HASHTABLE, *PHASHTABLE ;  

class StringHash
{
public:
	StringHash(const long nTableLength = MAXTABLELEN);
	~StringHash(void);
private:  
	unsigned long cryptTable[0x500];  
	unsigned long m_tablelength;    
	HASHTABLE *m_HashIndexTable; 
private:
	void InitCryptTable();                                             
	unsigned long HashString(const string& lpszString, unsigned long dwHashType);    
public:
	bool Hash(string url);
	unsigned long Hashed(string url);    
	HASHTABLE GetStringHashTable(unsigned long pos){ return m_HashIndexTable[pos]; }
	unsigned long GetTableLength(void) { return m_tablelength; }
};
#endif
