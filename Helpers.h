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

#define DECLARE_CMDS_LIST extern CMD cmdsList[99];

#define BEGIN_DECLARE_CMDS CMD cmdsList[99] = {

#define END_DECLARE_CMDS };

#define ADD_CMD(cmd_name, func)               \
    std::make_tuple(L#cmd_name, func),

#define REGISTER_CMDS(callback)                                               \
for (const auto& cmd_func : cmdsList) {                                       \
    callback(cmd_func);                                                       \
};

#undef HANDLE
#ifndef HANDLE
#define HANDLE
template <typename T>
struct Handle
{
public:
	Handle()
	{
		Init();
	}
	~Handle()
	{
		DecrementRef();

		if (*refCount == 0) {
			if (p)
			{
				p->close();
				p = nullptr;
				//delete p; // for we get pointer for Adobe systems
			}
			delete refCount;
		}
	}
	Handle(const Handle<T>& _src) :p(_src.p), refCount(_src.refCount)
	{
		AddRef();
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
	void  operator=(T* _p) {
		p = _p;
	}
	//T* & get() {
	//	return p;
	//}

private:
	void Init()
	{
		refCount = new std::size_t(1); // we have set ref as 0
	}
	void AddRef()
	{
		if (!refCount) Init();
		++(*refCount);
	}
	void DecrementRef()
	{
		--(*refCount);
	}
private:
	T* p = nullptr;
	std::size_t* refCount = nullptr;
};
#endif // HANDLE

#endif