#ifndef ArrayListH
#define ArrayListH

#include <vector>
#include <istream>
#include <ostream>
#include <iterator>
using namespace std;
//---------------------------------------------------------------------------
template <class T>
class ArrayList : public vector<T>
{
public:
	typename vector<T>::iterator Begin()
    {
        return vector<T>::begin();
    }
	typename vector<T>::iterator End()
    {
        return vector<T>::end();
    }
	bool IsEmpty()
    {
        return vector<T>::empty();
    }

	void Add(const T &value) 
    {
        vector<T>::push_back(value);
    }
	void Add()
    {
        T p; vector<T>::push_back(p);
    }
	void AddRange(const T* array, const int count)
	{
		for(int i  = 0 ; i < count ; i++)
		{
			vector<T>::push_back(array[i]);
		}
		return;
	}
	
	void Insert(int index, const T &value) 
	{
		typename vector<T>::iterator it = vector<T>::begin() + index;
		vector<T>::insert(it, value);
	}
	
	void Delete()
	{
		vector<T>::pop_back();
	}
	void Remove(int index) 
	{
		typename vector<T>::iterator it = vector<T>::begin() + index;
		vector<T>::erase(it);
	}
	
	void Assign(int count, const T& value)
	{
		if(count <= 0) return;
		vector<T>::assign(count, value);
	}
	void Assign(int count)
	{
		if(count <= 0) return;
		T value;
		vector<T>::assign(count, value);
	}
	int     GetCount() const
	{
		if(!vector<T>::empty())
		{
			return (int)(vector<T>::size());
		}
		return 0;
	}
	void    Clear() {vector<T>::clear();}
	void    Write(ostream& out) {
		vector<T>::copy(vector<T>::begin(), vector<T>::end(), ostream_iterator<T>(out, "\n"));
	}
	void    Read(istream& in) {
		vector<T>::copy(istream_iterator<T>(in), istream_iterator<T>(), vector<T>::inserter(*this, vector<T>::begin()));
	}
    
	ArrayList()
	{
	}
	
	ArrayList(int count, int defaultValue)
	{
		vector<T>(count, defaultValue);
	}
	
	~ArrayList()
	{
	}
};
#endif
