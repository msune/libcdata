#include "cdata/set.h"
#include "common_int.h"
#include "set_int.h"

#include <string.h>

using namespace std;

cdata_set_t* cdata_set_create(const uint16_t key_size){

	__cdata_set_int_t* m = NULL;

	if(key_size == 0)
		return m;

	m = (__cdata_set_int_t*)malloc(sizeof(__cdata_set_int_t));
	memset(m, 0, sizeof(__cdata_set_int_t));
	m->magic_num = CDATA_MAGIC;
	m->user_key_len = key_size;

	try{
		if(key_size == 1){
			m->set.u8 = new set<uint8_t>();
			m->key_len = 1;
		}else if(key_size == 2){
			m->set.u16 = new set<uint16_t>();
			m->key_len = 2;
		}else if(key_size > 2 && key_size <= 4){
			m->set.u32 = new set<uint32_t>();
			m->key_len = 4;
		}else if(key_size > 4 && key_size <= 8){
			m->set.u64 = new set<uint64_t>();
			m->key_len = 8;
		}else if(key_size > 8 && key_size <= 16){
			m->set.u128 = new set<cdata_u128_t>();
			m->key_len = 16;
		}else if(key_size > 16 && key_size <= 32){
			m->set.u256 = new set<cdata_u256_t>();
			m->key_len = 32;
		}else if(key_size > 32 && key_size <= 64){
			m->set.u512 = new set<cdata_u512_t>();
			m->key_len = 64;
		}else if(key_size > 64 && key_size <= 128){
			m->set.u1024 = new set<cdata_u1024_t>();
			m->key_len = 128;
		}else if(key_size > 128 && key_size <= 256){
			m->set.u2048 = new set<cdata_u2048_t>();
			m->key_len = 256;
		}else{
			//Variable
			//TODO
			goto ROLLBACK;
		}
	}catch(bad_alloc& e){
		goto ROLLBACK;
	}catch(...){
		CDATA_ASSERT(0);
		goto ROLLBACK;
	}

	return m;

ROLLBACK:
	free(m);
	return NULL;
};

/**
* Destroy a set structure
*/
int cdata_set_destroy(cdata_set_t* set){

	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	CDATA_CHECK_MAGIC(m);

	try{
		switch(m->key_len){
			case 1:
				delete m->set.u8;
				break;
			case 2:
				delete m->set.u16;
				break;
			case 4:
				delete m->set.u32;
				break;
			case 8:
				delete m->set.u64;
				break;
			case 16:
				delete m->set.u128;
				break;
			case 32:
				delete m->set.u256;
				break;
			case 64:
				delete m->set.u512;
				break;
			case 128:
				delete m->set.u1024;
				break;
			case 256:
				delete m->set.u2048;
				break;
			default:
				//TODO
				CDATA_ASSERT(0);
				break;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	m->magic_num = 0x0;
	free(m);

	return CDATA_SUCCESS;
}

int cdata_set_clear(cdata_set_t* set){

	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	CDATA_CHECK_MAGIC(m);

	try{
		if(m->key_len == 1){
			m->set.u8->clear();
		}else if(m->key_len ==  2){
			m->set.u16->clear();
		}else if(m->key_len > 2 && m->key_len <= 4){
			m->set.u32->clear();
		}else if(m->key_len > 4 && m->key_len <= 8){
			m->set.u64->clear();
		}else if(m->key_len > 8 && m->key_len <= 16){
			m->set.u128->clear();
		}else if(m->key_len > 16 && m->key_len <= 32){
			m->set.u256->clear();
		}else if(m->key_len > 32 && m->key_len <= 64){
			m->set.u512->clear();
		}else if(m->key_len > 64 && m->key_len <= 128){
			m->set.u1024->clear();
		}else if(m->key_len > 128 && m->key_len <= 256){
			m->set.u2048->clear();
		}else{
			//Variable
			//TODO
			return CDATA_E_UNSUPPORTED;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

bool cdata_set_empty(cdata_set_t* set){

	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	if(!m || m->magic_num != CDATA_MAGIC)
		return false;

	try{
		switch(m->key_len){
			case 1:
				return m->set.u8->empty();
			case 2:
				return m->set.u16->empty();
			case 3:
				return m->set.u32->empty();
			case 4:
				return m->set.u64->empty();
			case 8:
				return m->set.u128->empty();
			case 16:
				return m->set.u256->empty();
			case 32:
				return m->set.u512->empty();
			case 64:
				return m->set.u1024->empty();
			case 128:
				return m->set.u2048->empty();
			default:
				//Variable
				//TODO
				return false;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return false;
	}

	return false;
}

uint32_t cdata_set_size(cdata_set_t* set){

	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	if(!m || m->magic_num != CDATA_MAGIC)
		return 0;

	try{
		switch(m->key_len){
			case 1:
				return m->set.u8->size();
			case 2:
				return m->set.u16->size();
			case 3:
				return m->set.u32->size();
			case 4:
				return m->set.u64->size();
			case 8:
				return m->set.u128->size();
			case 16:
				return m->set.u256->size();
			case 32:
				return m->set.u512->size();
			case 64:
				return m->set.u1024->size();
			case 128:
				return m->set.u2048->size();
			default:
				//Variable
				//TODO
				return 0;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return 0;
	}

	return 0;
}

template<typename T>
int cdata_set_insert_u(__cdata_set_int_t* m, std::set<T>* m_u,
							const void* key){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		if(m_u->find(*aux) != m_u->end())
			return CDATA_E_EXISTS;
		m_u->insert(*aux);

		return CDATA_SUCCESS;
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	if(m_u->find(aux) != m_u->end())
		return CDATA_E_EXISTS;

	m_u->insert(aux);

	return CDATA_SUCCESS;
}

int cdata_set_insert(cdata_set_t* set, const void* key){

	int rv;
	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	CDATA_CHECK_MAGIC(m);

	if(!key)
		return CDATA_E_INVALID;

	//NOTE: we don't want std::set insert "replace semantics", so we return
	//E_EXISTS if key is present in the set
	try{
		switch(m->key_len){
			case 1:
				rv = cdata_set_insert_u<uint8_t>(m, m->set.u8,
									key);
				break;
			case 2:
				rv = cdata_set_insert_u<uint16_t>(m, m->set.u16,
									key);
				break;
			case 4:
				rv = cdata_set_insert_u<uint32_t>(m, m->set.u32,
									key);
				break;
			case 8:
				rv = cdata_set_insert_u<uint64_t>(m, m->set.u64,
									key);
				break;
			case 16:
				rv = cdata_set_insert_u<cdata_u128_t>(m,
								m->set.u128,
								key);
				break;
			case 32:
				rv = cdata_set_insert_u<cdata_u256_t>(m,
								m->set.u256,
								key);
				break;
			case 64:
				rv = cdata_set_insert_u<cdata_u512_t>(m,
								m->set.u512,
								key);
				break;
			case 128:
				rv = cdata_set_insert_u<cdata_u1024_t>(m,
								m->set.u1024,
								key);
				break;
			case 256:
				rv = cdata_set_insert_u<cdata_u2048_t>(m,
								m->set.u2048,
								key);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

template<typename T>
int cdata_set_erase_u(__cdata_set_int_t* m, std::set<T>* m_u,
							const void* key){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		if(m_u->find(*aux) == m_u->end())
			return CDATA_E_NOT_FOUND;
		m_u->erase(*aux);

		return CDATA_SUCCESS;
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	if(m_u->find(aux) == m_u->end())
		return CDATA_E_NOT_FOUND;

	m_u->erase(aux);

	return CDATA_SUCCESS;
}

int cdata_set_erase(cdata_set_t* set, const void* key){

	int rv;
	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	CDATA_CHECK_MAGIC(m);

	if(!key)
		return CDATA_E_INVALID;

	try{
		switch(m->key_len){
			case 1:
				rv = cdata_set_erase_u<uint8_t>(m, m->set.u8,
									key);
				break;
			case 2:
				rv = cdata_set_erase_u<uint16_t>(m, m->set.u16,
									key);
				break;
			case 4:
				rv = cdata_set_erase_u<uint32_t>(m, m->set.u32,
									key);
				break;
			case 8:
				rv = cdata_set_erase_u<uint64_t>(m, m->set.u64,
									key);
				break;
			case 16:
				rv = cdata_set_erase_u<cdata_u128_t>(m,
								m->set.u128,
								key);
				break;
			case 32:
				rv = cdata_set_erase_u<cdata_u256_t>(m,
								m->set.u256,
								key);
				break;
			case 64:
				rv = cdata_set_erase_u<cdata_u512_t>(m,
								m->set.u512,
								key);
				break;
			case 128:
				rv = cdata_set_erase_u<cdata_u1024_t>(m,
								m->set.u1024,
								key);
				break;
			case 256:
				rv = cdata_set_erase_u<cdata_u2048_t>(m,
								m->set.u2048,
								key);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}


template<typename T>
bool cdata_set_find_u(__cdata_set_int_t* m, std::set<T>* m_u,
							const void* key){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;
		aux = (T*)key;
		return m_u->find(*aux) != m_u->end();
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	return m_u->find(aux) != m_u->end();
}

bool cdata_set_find(cdata_set_t* set, const void* key){

	bool rv;
	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	if(!m || m->magic_num != CDATA_MAGIC || !key)
		return false;

	try{
		switch(m->key_len){
			case 1:
				rv = cdata_set_find_u<uint8_t>(m, m->set.u8,
									key);
				break;
			case 2:
				rv = cdata_set_find_u<uint16_t>(m, m->set.u16,
									key);
				break;
			case 4:
				rv = cdata_set_find_u<uint32_t>(m, m->set.u32,
									key);
				break;
			case 8:
				rv = cdata_set_find_u<uint64_t>(m, m->set.u64,
									key);
				break;
			case 16:
				rv = cdata_set_find_u<cdata_u128_t>(m,
								m->set.u128,
								key);
				break;
			case 32:
				rv = cdata_set_find_u<cdata_u256_t>(m,
								m->set.u256,
								key);
				break;
			case 64:
				rv = cdata_set_find_u<cdata_u512_t>(m,
								m->set.u512,
								key);
				break;
			case 128:
				rv = cdata_set_find_u<cdata_u1024_t>(m,
								m->set.u1024,
								key);
				break;
			case 256:
				rv = cdata_set_find_u<cdata_u2048_t>(m,
								m->set.u2048,
								key);
				break;
			default:
				//Variable
				//TODO
				return false;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return false;
	}

	return rv;
}

template<typename T>
void cdata_set_traverse_u(const cdata_set_t* set, std::set<T>* m_u,
							cdata_set_it f,
							void* opaque){

	typename std::set<T>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end(); ++it){
		const T& t = *it;
		(*f)(set, &t, opaque);
	}
}

int cdata_set_traverse(const cdata_set_t* set, cdata_set_it f, void* opaque){

	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	CDATA_CHECK_MAGIC(m);

	if(!f)
		return CDATA_E_INVALID;

	try{
		switch(m->key_len){
			case 1:
				cdata_set_traverse_u<uint8_t>(m, m->set.u8, f,
									opaque);
				break;
			case 2:
				cdata_set_traverse_u<uint16_t>(m, m->set.u16, f,
									opaque);
				break;
			case 4:
				cdata_set_traverse_u<uint32_t>(m, m->set.u32, f,
									opaque);
				break;
			case 8:
				cdata_set_traverse_u<uint64_t>(m, m->set.u64, f,
									opaque);
				break;
			case 16:
				cdata_set_traverse_u<cdata_u128_t>(m,
								m->set.u128, f,
								opaque);
				break;
			case 32:
				cdata_set_traverse_u<cdata_u256_t>(m,
								m->set.u256, f,
								opaque);
				break;
			case 64:
				cdata_set_traverse_u<cdata_u512_t>(m,
								m->set.u512, f,
								opaque);
				break;
			case 128:
				cdata_set_traverse_u<cdata_u1024_t>(m,
								m->set.u1024, f,
								opaque);
				break;
			case 256:
				cdata_set_traverse_u<cdata_u2048_t>(m,
								m->set.u2048, f,
								opaque);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

template<typename T>
void cdata_set_rtraverse_u(const cdata_set_t* set, std::set<T>* m_u,
							cdata_set_it f,
							void* opaque){

	typename std::set<T>::const_reverse_iterator it;

	for(it = m_u->rbegin(); it != m_u->rend(); ++it){
		const T& t = *it;
		(*f)(set, &t, opaque);
	}
}

int cdata_set_rtraverse(const cdata_set_t* set, cdata_set_it f, void* opaque){

	__cdata_set_int_t* m = (__cdata_set_int_t*)set;

	CDATA_CHECK_MAGIC(m);

	if(!f)
		return CDATA_E_INVALID;

	try{
		switch(m->key_len){
			case 1:
				cdata_set_rtraverse_u<uint8_t>(m, m->set.u8, f,
									opaque);
				break;
			case 2:
				cdata_set_rtraverse_u<uint16_t>(m, m->set.u16,
									f,
									opaque);
				break;
			case 4:
				cdata_set_rtraverse_u<uint32_t>(m, m->set.u32,
									f,
									opaque);
				break;
			case 8:
				cdata_set_rtraverse_u<uint64_t>(m, m->set.u64,
									f,
									opaque);
				break;
			case 16:
				cdata_set_rtraverse_u<cdata_u128_t>(m,
								m->set.u128, f,
								opaque);
				break;
			case 32:
				cdata_set_rtraverse_u<cdata_u256_t>(m,
								m->set.u256, f,
								opaque);
				break;
			case 64:
				cdata_set_rtraverse_u<cdata_u512_t>(m,
								m->set.u512, f,
								opaque);
				break;
			case 128:
				cdata_set_rtraverse_u<cdata_u1024_t>(m,
								m->set.u1024, f,
								opaque);
				break;
			case 256:
				cdata_set_rtraverse_u<cdata_u2048_t>(m,
								m->set.u2048, f,
								opaque);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}