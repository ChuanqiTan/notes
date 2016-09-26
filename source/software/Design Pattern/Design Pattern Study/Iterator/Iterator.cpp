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


//��ǰ����
template<typename ItemType> class VectorCollection;
template<typename ItemType> class ListCollection;


//����������,��ɵ�������Ľӿ�
template<typename ItemType>
class AbstractIterator
{
public:
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual ItemType& CurrentItem() = 0;
};


//���Ե���vector�ĵ�����
template<typename ItemType>
class VectorIterator : public AbstractIterator<ItemType>
{
public:
	VectorIterator(VectorCollection<ItemType> * const collection)
		: _collection(collection), _collection_time(collection->_collection_altered_time)
	{}

	void First()
	{		
		_collection_time = _collection->_collection_altered_time;	//���µ���ʱӦ�ø��¼�¼ʱ��
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

		//������������ĩβ
		if (IsDone())
		{
			throw new exception("out of range");
		}

		return _collection->_collection[_postion];
	}

private:
	//���������κβ���֮ǰ��Ӧ�ü��һ�µ������Ƿ���Ч
	//���ּ�¼ʱ��ķ�������"�̰߳�ȫ��",���ǶԵ��̵߳��������������Ч��
	void CheckValid() 
	{
		//�����ǰ�ļ��ϵ�����޸�ʱ�����¼�Ĳ���,��ʾ���ϱ��޸�,������ʧЧ,����Ӧ��������ֹ
		if (_collection->_collection_altered_time != _collection_time)
		{
			throw new exception("collection has been modify, iterator are invalid");
		}
	}

private:
	size_t _postion;
	VectorCollection<ItemType> *_collection;
	time_t _collection_time;		//���ڼ�¼��ʼ����ʱ���ϵ�����޸�ʱ��
};


//���Ե���list�ĵ�����
template<typename ItemType>
class ListIterator : public AbstractIterator<ItemType>
{
public:
	ListIterator(ListCollection<ItemType> * const collection)
		: _collection(collection), _collection_time(collection->_collection_altered_time)
	{}

	void First()
	{
		_collection_time = _collection->_collection_altered_time;	//���µ���ʱӦ�ø��¼�¼ʱ��
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
	//���������κβ���֮ǰ��Ӧ�ü��һ�µ������Ƿ���Ч
	//���ּ�¼ʱ��ķ�������"�̰߳�ȫ��",���ǶԵ��̵߳��������������Ч��
	void CheckValid() 
	{
		//�����ǰ�ļ��ϵ�����޸�ʱ�����¼�Ĳ���,��ʾ���ϱ��޸�,������ʧЧ,����Ӧ��������ֹ
		if (_collection->_collection_altered_time != _collection_time)
		{
			throw new exception("collection has been modify, iterator are invalid");
		}
	}

private:
	ListCollection<ItemType> *_collection;
	size_t _postion;
	time_t _collection_time;		//���ڼ�¼��ʼ����ʱ���ϵ�����޸�ʱ��
};


//���ϵĳ������
template<typename ItemType>
class AbstractCollection
{
public:
	virtual void Add(ItemType) = 0;

	//���Դ�����Ӧ�ĵ�������Factory Method����
	virtual auto_ptr< AbstractIterator<ItemType> > CreateIterator() = 0;
};


//��vectorΪ�����ļ�����
template<typename ItemType>
class VectorCollection : public AbstractCollection<ItemType>
{
public:
	friend class VectorIterator<ItemType>;		//����������Ϊ��Ԫ

	VectorCollection()	
		: _collection_altered_time(time(NULL))
	{}

	void Add(ItemType item)
	{
		//�����κθ��¼��ϵĲ���(�����,�޸�,ɾ��)ʱ,��������¼��ϵ�����޸�ʱ��
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
	time_t _collection_altered_time;		//��ʶ�ü��ϵ�����޸�ʱ��
};


//��listΪ�����ļ�����
template<typename ItemType>
class ListCollection : public AbstractCollection<ItemType>
{
public:
	friend class ListIterator<ItemType>;		//����������Ϊ��Ԫ

	ListCollection()
		: _collection_altered_time(time(NULL))
	{}

	void Add(ItemType item)
	{
		//�����κθ��¼��ϵĲ���(�����,�޸�,ɾ��)ʱ,��������¼��ϵ�����޸�ʱ��
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
	time_t _collection_altered_time;		//��ʶ�ü��ϵ�����޸�ʱ��
};


//�Լ�����ÿ��Ԫ��ʹ�õ�ģ�巽��
template<typename ItemType>
void display(ItemType &item)
{
	cout << item << endl;
}

//��������ģ�巽��
template<typename ItemType>
bool Filter(ItemType item)
{
	return item % 2 == 0;
}


//�ڲ��������������˹��ܵ�
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
			if (_filter(iter->CurrentItem()))	//��ʾ���˹��ܣ����������ڲ�����ʱʵ��
			{
				func(iter->CurrentItem());		//��ͨ���˹��˵�Ԫ�ص�����Ҫ����ķ���
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

	//��ʹ�ó���ӿ�,����ν����������ʲô. 
	//������newһ��VectorCollection��ListCollection������Ĵ�����˵û������
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
