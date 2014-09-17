
/* 我们的目的是要设计出一种方法，能够让我不必去复制对象，同时能够达到运行时绑定对象的方法——handle类

- handle类行为类似指针，复制handle对象不会复制其基础对象，复制之后，两个handle指向同一个基础对象。
创建一个handle对象，用户需要传递属于有handle管理类型的动态分配对象的地址，从此刻起，handle将拥有这个对象，
并且一旦不在有handle对象与该对象关联，handle类负责删除该对象。*/
~~~
#ifndef MYHANDLE
#define MYHANDLE

template<typename T>
class Handle
{
public:
	//默认构造函数
	Handle(T *p = 0):ptr(p),use(new size_t(1)){}
	//复制构造函数
	Handle(const Handle & rhs):ptr(rhs.ptr),use(rhs.use){(*use)++;}
	//赋值函数
	Handle & operator=(const Handle & rhs)
	{
		*(rhs.use)++;
		removeRef();
		ptr = rhs.ptr;
		use = rhs.use;
		return *this;
	}
	//析构函数
	~Handle(){removeRef();}

	//指针解引用和箭头操作符，两个版本
	T& operator*();
	T* operator->();
	const T& operator*() const;
	const T* operator->() const;
private:
	T * ptr;
	size_t * use;
	void removeRef()
	{
		if (--(*use) == 0)
		{
			delete ptr;
			delete use;
		}
	}
};

//指针解引用和箭头操作符，两个版本
template<typename T> inline T& Handle<T>::operator *()
{
	if (ptr) return *ptr;
	throw std::runtime_error("dereference of unbound Handle");
}
template<typename T> inline T* Handle<T>::operator->()
{
	if (ptr) return ptr;
	throw std::runtime_error("access through unbound Handle");
}
template<typename T> inline const T& Handle<T>::operator *() const
{
	if (ptr) return *ptr;
	throw std::runtime_error("dereference of unbound Handle");
}
template<typename T> inline const T* Handle<T>::operator->() const
{
	if (ptr) return ptr;
	throw std::runtime_error("access through unbound Handle");
}
#endif
~~~
