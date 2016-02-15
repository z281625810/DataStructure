/* ***  Author:  Feng Sun
*  Last Update:  Octorber 4 , 2014
*        Class:  CSI-281
*     Filename:  doublyLinkedList.h
*
*  Description:
*      This class is template class for a doubly linked list
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList
{
private:
	template <typename T>
	struct Node
	{
		T       mData;
		Node<T> *mNext, *mPrevious;

		/*      Pre:  None
		*     Post:  This object is initialized using default values
		*  Purpose:  To intialize date object
		*************************************************************************/
		Node()
		{
			mData = T();
			mNext = NULL;
			mPrevious = NULL;
		}


		/*      Pre:  None
		*     Post:  This object is initialized using specified data
		*  Purpose:  To intialize date object
		*************************************************************************/
		Node(T data)
		{
			mData = data;
			mNext = NULL;
			mPrevious = NULL;
		}
	};

	Node<T> *mHead, *mTail;
	int     mCount;

public:
	DoublyLinkedList();
	~DoublyLinkedList();

	int  getCount();
	T    getData(int index);
	void setData(int index, T data);

	void clear();
	void display();
	void displayInReverse();
	void insert(T data);
	void insertAsUnsorted(T data);
	bool isEmpty();
	bool isExist(T searchKey);
	bool isExistBinarySearch(T searchKey);
	bool remove(T searchKey);
	T    removeAt(int index);
};


#endif //! Doubly_Linked_List_h