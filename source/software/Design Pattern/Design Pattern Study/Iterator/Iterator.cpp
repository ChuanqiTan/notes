// Iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <vector>
#include <list>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <algorithm>
#include <ctime>
using namespace std;


//提前声明
template<typename ItemType> class VectorCollection;
template<typename ItemType> class ListCollection;


//迭代器基类,完成迭代所需的接口
template<typename ItemType>
class AbstractIterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual ItemType& CurrentItem() = 0;
};


//用以迭代vector的迭代器
template<typename ItemType>
class VectorIterator : public AbstractIterator<ItemType>
{
public:
	VectorIterator(VectorCollection<ItemType> * const collection)
		: _collection(collection), _collection_time(collection->_collection_altered_time)
	{}

	void First()
	{		
		_collection_time = _collection->_collection_altered_time;	//重新迭代时应该更新记录时间
		_postion = 0;
	}

	void Next()
	{
		CheckValid();
		++_postion;
	}

	bool IsDone()
	{
		CheckValid();
		return _postion >= _collection->_collection.size();
	}

	ItemType& CurrentItem()
	{
		CheckValid();

		//迭代器超过了末尾
		if (IsDone())
		{
			throw new exception("out of range");
		}

		return _collection->_collection[_postion];
	}

private:
	//迭代器做任何操作之前都应该检查一下迭代器是否有效
	//这种记录时间的方法不是"线程安全的",但是对单线程的情况是适用且有效的
	void CheckValid() 
	{
		//如果当前的集合的最后修改时间与记录的不符,表示集合被修改,迭代器失效,迭代应该立即中止
		if (_collection->_collection_altered_time != _collection_time)
		{
			throw new exception("collection has been modify, iterator are invalid");
		}
	}

private:
	size_t _postion;
	VectorCollection<ItemType> *_collection;
	time_t _collection_time;		//用于记录开始迭代时集合的最后修改时间
};


//用以迭代list的迭代器
template<typename ItemType>
class ListIterator : public AbstractIterator<ItemType>
{
public:
	ListIterator(ListCollection<ItemType> * const collection)
		: _collection(collection), _collection_time(collection->_collection_altered_time)
	{}

	void First()
	{
		_collection_time = _collection->_collection_altered_time;	//重新迭代时应该更新记录时间
		_postion = 0;
	}

	void Next()
	{
		CheckValid();
		++_postion;
	}

	bool IsDone()
	{
		CheckValid();
		return _postion >= _collection->_list.size();
	}

	ItemType& CurrentItem()
	{
		CheckValid();

		if (IsDone())
		{
			throw new exception("out of range");
		}

		list<ItemType>::iterator iter = _collection->_list.begin();
		for (size_t pos = 0; pos < _postion && iter != _collection->_list.end(); ++pos)
		{
			++iter;
		}

		return *iter;
	}

private:
	//迭代器做任何操作之前都应该检查一下迭代器是否有效
	//这种记录时间的方法不是"线程安全的",但是对单线程的情况是适用且有效的
	void CheckValid() 
	{
		//如果当前的集合的最后修改时间与记录的不符,表示集合被修改,迭代器失效,迭代应该立即中止
		if (_collection->_collection_altered_time != _collection_time)
		{
			throw new exception("collection has been modify, iterator are invalid");
		}
	}

private:
	ListCollection<ItemType> *_collection;
	size_t _postion;
	time_t _collection_time;		//用于记录开始迭代时集合的最后修改时间
};


//集合的抽象基类
template<typename ItemType>
class AbstractCollection
{
public:
	virtual void Add(ItemType) = 0;

	//用以创建相应的迭代器的Factory Method方法
	virtual auto_ptr< AbstractIterator<ItemType> > CreateIterator() = 0;
};


//以vector为基础的集合类
template<typename ItemType>
class VectorCollection : public AbstractCollection<ItemType>
{
public:
	friend class VectorIterator<ItemType>;		//声明迭代器为友元

	VectorCollection()	
		: _collection_altered_time(time(NULL))
	{}

	void Add(ItemType item)
	{
		//在做任何更新集合的操作(如添加,修改,删除)时,都必须更新集合的最后修改时间
		_collection_altered_time = time(NULL);	

		_collection.push_back(item);
	}

	virtual auto_ptr< AbstractIterator<ItemType> > CreateIterator()
	{
		auto_ptr< AbstractIterator<ItemType> > ptr(new VectorIterator<ItemType>(this));

		return ptr;
	}

private:
	vector<ItemType> _collection;
	time_t _collection_altered_time;		//标识该集合的最后修改时间
};


//以list为基础的集合类
template<typename ItemType>
class ListCollection : public AbstractCollection<ItemType>
{
public:
	friend class ListIterator<ItemType>;		//声明迭代器为友元

	ListCollection()
		: _collection_altered_time(time(NULL))
	{}

	void Add(ItemType item)
	{
		//在做任何更新集合的操作(如添加,修改,删除)时,都必须更新集合的最后修改时间
		_collection_altered_time = time(NULL);	

		_list.push_back(item);
	}

	virtual auto_ptr< AbstractIterator<ItemType> > CreateIterator()
	{
		auto_ptr< AbstractIterator<ItemType> > ptr(new ListIterator<ItemType>(this));

		return ptr;
	}

private:
	list<ItemType> _list;
	time_t _collection_altered_time;		//标识该集合的最后修改时间
};


//对集合中每个元素使用的模板方法
template<typename ItemType>
void display(ItemType &item)
{
	cout << item << endl;
}

//过滤器的模板方法
template<typename ItemType>
bool Filter(ItemType item)
{
	return item % 2 == 0;
}


//内部迭代器，带过滤功能的
template<typename ItemType>
class InnerFilterIterator
{
public:
	InnerFilterIterator(AbstractCollection<ItemType> &collection, bool (*filter)(ItemType))
		: _collection(collection), _filter(filter)
	{}

	void ProcessItems(void (*func)(ItemType &))
	{
		auto_ptr< AbstractIterator<ItemType> > iter = _collection.CreateIterator();
		for (iter->First(); !iter->IsDone(); iter->Next())
		{
			if (_filter(iter->CurrentItem()))	//演示过滤功能，很容易在内部迭代时实现
			{
				func(iter->CurrentItem());		//对通过了过滤的元素调用需要处理的方法
			}
		}
	}

private:
	AbstractCollection<ItemType> &_collection;
	bool (*_filter)(ItemType);
};


void main()
{
	AbstractCollection<int> *abc;

	//仅使用抽象接口,无所谓具体类型是什么. 
	//在这里new一个VectorCollection或ListCollection对下面的代码来说没有区别
	abc = new VectorCollection<int>();
	//abc = new ListCollection<int>();

	for (int i = 0; i < 10; ++i)
	{
		abc->Add(i);
	}

	cout << "Show outer-iterator" << endl;
	auto_ptr< AbstractIterator<int> > iter = abc->CreateIterator();
	for (iter->First(); !iter->IsDone(); iter->Next())
	{
		cout << iter->CurrentItem() << endl;
	}

	cout << "Show inner-iterator" << endl;
	InnerFilterIterator<int> inner_iter(*abc, Filter<int>);
	inner_iter.ProcessItems(display<int>);
}
