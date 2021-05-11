#pragma once
#ifndef HELPERS
#define HELPERS

#ifndef CMDS
#define CMDS
typedef void (*cmd_func)();

#include "AdAChar.h"
#include <tuple>
typedef std::tuple<const ACHAR*, cmd_func> CMD;
#endif
#

#define Hi() MessageBoxA(0, "Hi", "", 0);
#define DECLARE_CMDS_LIST extern CMD cmdsList[];

#define BEGIN_DECLARE_CMDS CMD cmdsList[] = {

#define END_DECLARE_CMDS };

#define ADD_CMD(cmd_name, func)               \
    std::make_tuple(L##cmd_name, func),

#define REGISTER_CMDS(callback)                                               \
for (const auto& cmd_func : cmdsList) {                                       \
    callback(cmd_func);                                                       \
};

#undef HANDLE
#ifndef HANDLE
#define HANDLE

//template <typename T>
//class PlainHandle
//{
//public:
//	// 我们把 空指针 看作一个“引用”
//	// 稍后设置
//	// 释放的时候，如果设置，那么就 close
//	typedef enum {
//		eNew,
//		//eAPI
//	} PointerType;
//	PlainHandle(T* _p = nullptr, PointerType _pType = eNew) // case0 : construct from "new pointer"
//	{
//		Init();
//		AddRef();
//
//		pType = _pType;
//		if (_p) {
//			p = _p;
//		}
//		else {
//			// 延迟设置指针
//		}
//	}
//	~PlainHandle()
//	{
//		Destruct();
//	}
//	PlainHandle(const PlainHandle<T>& _src) // case1 : construct from exsisting handle
//	{
//		if (&_src != this) {
//			Destruct();
//
//			p = _src.p;
//			pType = _src->pType;
//			pRefCount = _src.pRefCount;
//			AddRef();
//		}
//	}
//	T& operator*() {
//		return *p;
//	}
//	T*& operator->() {
//		return p;
//	}
//	T*& operator&() {
//		return p;
//	}
//	//operator T* ()
//	//{
//	//	return p;
//	//}
//	operator T*& ()
//	{
//		return p;
//	}
//	void  operator=(T* _p) {
//		if (p != _p) {
//			Destruct();
//
//			Init();
//			AddRef();
//			pType = eNew;
//			p = _p; // 无论指针是否为 nullptr，都形成完美的闭环
//		}
//		//return *this;
//	}
//	//T* & get() {
//	//	return p;
//	//}
//
//private:
//	void Init()
//	{
//		pRefCount = new std::size_t(0); // we have set ref as 0
//	}
//	void AddRef()
//	{
//		assert(pRefCount);
//
//		++(*pRefCount);
//	}
//	void DecrementRef()
//	{
//		assert(pRefCount);
//
//		--(*pRefCount);
//	}
//	void Destruct()
//	{
//		DecrementRef();
//
//		if (*pRefCount == 0) {
//			if (p)
//			{
//				delete p;
//				p = nullptr; // we get 'p' from Adobe System
//			}
//			delete pRefCount;
//		}
//	}
//private:
//	T* p = nullptr;
//	std::size_t* pRefCount = nullptr;
//	PointerType pType = eNew;
//};

template <typename T>
class Handle
{
public:
	// 我们把 空指针 看作一个“引用”
	// 稍后设置
	// 释放的时候，如果设置，那么就 close
	Handle(T* _p = nullptr) // case0 : construct from "new pointer"
	{
		Init();
		AddRef();

		if (_p) {
			p = _p;
		}
		else {
			// 延迟设置指针
		}
	}
	~Handle()
	{
		Destruct();
	}
	Handle(const Handle<T>& _src) // case1 : construct from exsisting handle
	{
		if (&_src != this) {
			Destruct();

			p = _src.p;
			pRefCount = _src.pRefCount;
			AddRef();
		}
	}
	T& operator*() {
		return *p;
	}
	T*& operator->() {
		return p;
	}
	T*& operator&() {
		return p;
	}
	void Delete() {
		if (p) {
			delete p;
		}
	}
	//operator T* () //
	//{
	//	return p;
	//}
	operator T*& ()
	{
		return p;
	}
	void  operator=(T* _p) {
		if (p != _p) {
			Destruct();

			Init();
			AddRef();
			p = _p; // 无论指针是否为 nullptr，都形成完美的闭环
		}
		//return *this;
	}
	//T* & get() {
	//	return p;
	//}

private:
	void Init()
	{
		pRefCount = new std::size_t(0); // we have set ref as 0
	}
	void AddRef()
	{
		assert(pRefCount);

		++(*pRefCount);
	}
	void DecrementRef()
	{
		assert(pRefCount);

		--(*pRefCount);
	}
	void Destruct()
	{
		DecrementRef();

		if (*pRefCount == 0) {
			if (p)
			{
				p->close();
				p = nullptr; // we get 'p' from Adobe System
			}
			delete pRefCount;
		}
	}
private:
	T* p = nullptr;
	std::size_t* pRefCount = nullptr;
};

#define H(TYPE, LOCAL_VAR) Handle<TYPE> LOCAL_VAR
//#define P(TYPE, LOCAL_VAR) PlainHandle<TYPE> LOCAL_VAR
#define P(TYPE, LOCAL_VAR) TYPE* LOCAL_VAR

#endif // HANDLE

#endif