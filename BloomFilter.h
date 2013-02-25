#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;
#include <openssl/md5.h>
#include "itoa.h"


class BloomFilter{
private:
		int m_ELEM_NUM;     // 
		double m_PERCENTAGE;// false positive percentage
		int m_hash_num;     // the number of hash function
		int m_vec_len;      // the length of the bloomfilter bit array
		vector<bool> m_vec; // the bloomfilter bit array
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

		void set(unsigned int elem){
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

		bool find(int elem){
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
