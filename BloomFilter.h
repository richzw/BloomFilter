#include <vector>
#include <cmath>
#include <cstdlib>

#include <openssl/md5.h>
#include "itoa.h"
#include "StringHash.h"
using namespace std;

class BloomFilter{
private:
		int m_ELEM_NUM;     // 
		double m_PERCENTAGE;// false positive percentage
		int m_hash_num;     // the number of hash function
		int m_vec_len;      // the length of the bloomfilter bit array
		vector<bool> m_vec; // the bloomfilter bit array
		
		StringHash m_mpq;
public:
		BloomFilter(int elem_num, double percentage):m_ELEM_NUM(elem_num),m_PERCENTAGE(percentage){
			init();
		}

		void init(){
			m_vec_len = (int)abs(m_ELEM_NUM*log(m_PERCENTAGE))/(log(2)*log(2)) + 1;
			m_hash_num = (int)(log(2)*((double)m_vec_len/m_ELEM_NUM));
			m_vec.reserve(m_vec_len);
			m_vec.resize(m_vec_len);
			for (size_t i = 0; i < m_vec.size(); ++i){
				m_vec[i] = false;
			}
		}
		
		/*
		 *@func: reset bloom filer to initialize status.
		 */
		void resetBloomFilter(){
			for (size_t i = 0; i < m_vec.size(); ++i){
				m_vec[i] = false;
			}
		}
		
		/*
		 * @func: insert element which type is int into the bloom filter
		 * @params: elem {unsigned int} the elemnt inserted into bloom filter
		 */
		void insertElementByMD5(unsigned int elem){
			char str_buffer[33];
			unsigned char result[MD5_DIGEST_LENGTH];
			int index = 0;

			// convert int to string
			int len = itoa(elem, str_buffer);
			for (int i = 0; i < m_hash_num; ++i){
				str_buffer[len] = i + '0';
				++len;
				MD5((unsigned char*)str_buffer, len, result);
				index = atoi(result)%m_vec_len;
				m_vec[index] = true;
				--len;
			}

		}

		/*
		 * @func: insert element which type is string into the bloom filter
		 * @params: str {string}, the element inserted into bloom filter
		 * @ret: true means insert successfully, otherwise, failed.
		 */
		bool insertElementByMPQ(string str){
			//TODO: need to check empty string?
			string tmp_str = str;
			int vec_index = 0;

			for (int num = 0; num < m_hash_num; ++num){
				tmp_str = str + string(num);

				if (m_mpq.Hash(str)){
					unsigned long pos = m_mpq.Hashed(str);
					HASHTABLE hash_table = m_mpq.GetStringHashTable(pos);
					//TODO: currently, just use nHashA, next to add nHashB.
					vec_index = hash_table.nHashA % m_vec_len;
					m_vec[vec_index] = true;
				}else
					return false;
				tmp_str = str;
			}
			return true;
		}

		/*
		 *@func: check the element which type is string locate in the bloom filter
		 *@params: str {string}, the element to be found.
		 *@ret: true, the element is in the bloom filter
		 @      false, the element is not in the bloom filter.
		 */
		bool isFountElement(string str){
			string tmp_str = str;
			int vec_index = 0;

			for (int num = 0; num < m_hash_num; ++num){
				tmp_str = str + string(num);

				if (m_mpq.Hash(str)){
					unsigned long pos = m_mpq.Hashed(str);
					HASHTABLE hash_table = m_mpq.GetStringHashTable(pos);
					//TODO: currently, just use nHashA, next to add nHashB.
					vec_index = hash_table.nHashA % m_vec_len;
					if (false == m_vec[vec_index])
						return false;
				}else
					return false;
				tmp_str = str;
			}
			return true;
			
		}

		/*
		 *@func: check the element which type is int locate in the bloom filter
		 *@param: elem {int}, the element to be found 
		 *@ret: true, the element is in the bloom filter
		 *      false, the element is not in the bloom filter
		 */
		bool isFoundElement(int elem){
			char str_buffer[33];
			unsigned char result[MD5_DIGEST_LENGTH];
			int index = 0;

			// convert int to string
			int len = itoa(elem, str_buffer);
			for (int i = 0; i < m_hash_num; ++i){
				str_buffer[len] = i + '0';
				++len;
				MD5((unsigned char*)str_buffer, len, result);
				index = atoi(result)%m_vec_len;
				if (false == m_vec[index])
					return false;
				--len;
			}
			
			return true;
		}

};
