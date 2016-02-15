/* ***  Author:  Feng Sun
*  Last Update:  September 10, 2014
*        Class:  CSI-281
*     Filename:  LinkedList.h
*
*  Description:
*      This is the template linked list definitions.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>

using namespace std;

template <typename T>
class LinkedList
{
	template <typename T>
	struct Node
	{
		T       mData;
		Node<T> *mNext;

		/*      Pre:  None
		*     Post:  This object is initialized using default values
		*  Purpose:  To initialize date object
		*************************************************************************/
		Node()
		{
			mData = T();
			mNext = NULL;
		}


		/*      Pre:  None
		*     Post:  This object is initialized using specified data
		*  Purpose:  To intialize date object
		*************************************************************************/
		Node(T data)
		{
			mData = data;
			mNext = NULL;
		}
	};


private:
	Node<T> *mHead, *mTail;
	int     mCount;

public:
	LinkedList();
	~LinkedList();

	int  getCount();
	T    getData(int index);
	void setData(int index, T data);

	void clear();
	void display();
	bool insert(T data);
	bool isEmpty();
	bool isExist(T searchKey);
	bool remove(T searchKey);
	T    removeAt(int index);

	T operator[](int index);
	LinkedList<T>& operator=(const LinkedList<T>& list); //copy assignment
	LinkedList<T>& operator+(LinkedList<T>& listTwo);
	LinkedList<T>& operator-(LinkedList<T>& listTwo);
};



#endif // !LinkedList_h