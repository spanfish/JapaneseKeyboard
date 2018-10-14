#ifndef TUATListH
#define TUATListH

#include <list>
using namespace std;
//---------------------------------------------------------------------------

template <class T>
class TUATList : public list<T>
{
public:
	void    Add(const T &value) 
	{
		list<T>::push_back(value);
	}
	
	void    Add()
	{
		T p; 
		list<T>::push_back(p);
	}
	
	void    AddRange(const T* array, const int count)
	{
		for(int i  = 0 ; i < count ; i++)
		{
			list<T>::push_back(array[i]);
		}
		return;
	}
	
	void Insert(int index, const T &value) 
	{
		typename list<T>::iterator it = list<T>::begin();
		for(int i = 0; i < index; ++i) ++it;
		list<T>::insert(it, value);
	}
	void Insert(typename list<T>::iterator it, const T &value)
	{
		list<T>::insert(it, value);
	}
	
	void    Delete()
	{
		list<T>::pop_back();
	}
	
	void    Remove(int index) 
	{
		typename list<T>::iterator it = list<T>::begin();
		for(int i = 0; i < index; ++i) ++it;
		list<T>::erase(it);
	}
	
	void    Remove(typename list<T>::iterator it) 
	{
		list<T>::erase(it);
	}
	
	int     GetCount() const
	{
		if(!list<T>::empty())
		{
			return (int)list<T>::size();
		}
		return 0;
	}
	
	void    Clear() {list<T>::clear();}
	
	typename list<T>::iterator operator[](const size_t index)  
	{
		typename list<T>::iterator it = list<T>::begin();
		for(size_t i = 0; i < index; ++i) ++it;
		return it;
	} 
	
	void    Assign(int count)
	{
		if(count <= 0) return;
		T value;
		list<T>::assign(count, value);
	}
	
	TUATList()
	{
	}
	
	TUATList(int count, int defaultValue)
	{
		list<T>(count, defaultValue);
	}
	
	~TUATList()
	{
	}
};
#endif