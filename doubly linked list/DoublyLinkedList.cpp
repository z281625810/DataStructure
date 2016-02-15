/* ***  Author:  Feng Sun
*  Last Update:  Octorber 4 , 2014
*        Class:  CSI-281
*     Filename:  doublyLinkedList.cpp
*
*  Description:
*      This class is template class for a doubly linked list implemention
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#include "DoublyLinkedList.h"

/*      Pre:  None
*     Post:  The next and previous pointers are initialized to NULL
*  Purpose:  Default constructor
******************************************************************************/
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	mHead = NULL;
	mTail = NULL;
	mCount = 0;
}

/*      Pre:  None
*     Post:  All the nodes in the list is deleted
*  Purpose:  To remove all the nodes in the list
*****************************************************************************/
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	// remove all nodes
	clear();

	// reinitialize the pointers
	mHead = NULL;
	mTail = NULL;

	// reinitialize count
	mCount = 0;
}


/*      Pre:  The object is instantiated
*     Post:  The number of nodes in the linked list is returned to the caller
*  Purpose:  To retrieve the number of nodes in the list
*****************************************************************************/
template <typename T>
int DoublyLinkedList<T>::getCount()
{
	return mCount;
}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  The data in the specified index is returned to the caller
*  Purpose:  To retrieve the specified nodes in the list
*****************************************************************************/
template <typename T>
T DoublyLinkedList<T>::getData(int index)
{
	if(mCount == 0 || index > mCount - 1|| index < 0)
	{
		return false;
	}
	else
	{
		int     i;
		Node<T> *tmp;

		tmp = mHead;
		for (i = 0; i < index; i++)
			tmp = tmp->mNext;

		return tmp->mData;
	}

}


/*      Pre:  The list is instantiated, the index is valid and the data is
*            available
*     Post:  The data in the specified index is updated with the specified
*            data
*  Purpose:  To update the specified nodes in the list
*****************************************************************************/
template <typename T>
void DoublyLinkedList<T>::setData(int index, T data)
{
	if(index < mCount && index >= 0)
	{
		int     i;
		Node<T> *tmp;

		tmp = mHead;
		for (i = 0; i < index; i++)
			tmp = tmp->mNext;

		tmp->mData = data;
	}
	else
	{
		cout << "invalid index" << endl;
	}
}

/*      Pre:  The list is initiated
*     Post:  All the nodes in the list is deleted
*  Purpose:  To remove all the nodes in the list
*****************************************************************************/
template <typename T>
void DoublyLinkedList<T>::clear()
{
	Node<T> *tmp = mHead;
	
	while(tmp != NULL)
	{
		mHead = mHead->mNext;
		delete tmp;
		mCount--;
		tmp = mHead;
	}
	mHead = mTail = NULL;
	
}
/*      Pre:  The dummy node is instantiated
*     Post:  The data of the nodes in the doubly linked list is displayed on
*            the screen
*  Purpose:  To display all data stored in the doubly linked list
******************************************************************************/
template <typename T>
void DoublyLinkedList<T>::display()
{
	Node<T> *tmp = mHead;
	if(mCount == 0)
	{
		cout << "NULL" << endl;
		return;
	}
	while (tmp != NULL)
	{
		cout << tmp->mData << " ";
		tmp = tmp->mNext;
	}
	cout << endl;
}


/*      Pre:  The dummy node is instantiated
*     Post:  The data of the nodes in the doubly linked list is displayed on
*            the screen in reverse order
*  Purpose:  To display all data stored in the doubly linked list in reverse
*            order
******************************************************************************/
template <typename T>
void DoublyLinkedList<T>::displayInReverse()
{
	Node<T> *tmp = mTail;
	if(mCount == 0)
	{
		cout << "NULL" << endl;
		return;
	}
	while (tmp != NULL)
	{
		cout << tmp->mData << " ";
		tmp = tmp->mPrevious;
	}
	cout << endl;
}


/*      Pre:  The dummy node is instantiated and the new value is available
*     Post:  The new node is added onto the doubly linked list in ascending
*            order.  For example, if the new data is B, then it must be added
*            in between A and C
*  Purpose:  To add a new node onto the doubly linked list
******************************************************************************/
template <typename T>
void DoublyLinkedList<T>::insert(T data)
{
	Node<T> *tmp, *newNode;
	newNode = new Node<T>(data);
	if (newNode == NULL)
		return;

	if (mHead == NULL)
	{
		mHead = newNode;
		mTail = newNode;
	}
	else
	{
		if (mHead->mData >= data)
		{
			mHead->mPrevious = newNode;
			newNode->mNext = mHead;
			mHead = newNode;
		}
		else if (mTail->mData <= data)
		{
			mTail->mNext = newNode;
			newNode->mPrevious = mTail;
			mTail = newNode;
		}
		else
		{
			tmp = mHead;
			while (tmp->mData < data)
			{
				tmp = tmp->mNext;
			}
			tmp->mPrevious->mNext = newNode;
			newNode->mPrevious = tmp->mPrevious;
			tmp->mPrevious = newNode;
			newNode->mNext = tmp;
			
		}
	}
	mCount++;
}

/*      Pre:  The dummy node is instantiated and the new value is available
*     Post:  The new node is added onto the doubly linked list without sorting
*  Purpose:  To add a new node onto the doubly linked list
******************************************************************************/
template <typename T>
void DoublyLinkedList<T>::insertAsUnsorted(T data)
{
	Node<T> *newNode;
	newNode = new Node<T>(data);
	if (newNode == NULL)
		return;

	if (mHead == NULL)
	{
		mHead = newNode;
		mTail = newNode;
	}
	else
	{
		mTail->mNext = newNode;
		newNode->mPrevious = mTail;
		mTail = newNode;
	}
	mCount++;
}

template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
	return mCount == 0;
}


/*      Pre:  The dummy node is instantiated and the searchkey is provided
*     Post:  True is the given value exists in the doubly linked list,
*            otherwise false
*  Purpose:  To validate if a given value exists in the doubly linked list
*            using binary search
******************************************************************************/
template <typename T>
bool DoublyLinkedList<T>::isExist(T searchKey)
{
	Node<T> *tmp = mHead;
	if (mHead == NULL)
	{
		return false;
	}
	else
	{
		while (tmp != NULL)
		{
			if (tmp->mData == searchKey)
			{
				return true;
			}
			tmp = tmp->mNext;
		}

		return false;
	}
}

/*      Pre:  The dummy node is instantiated and the searchkey is provided
*     Post:  True is the given value exists in the doubly linked list,
*            otherwise false
*  Purpose:  To validate if a given value exists in the doubly linked list
*            using sequential search
******************************************************************************/
template <typename T>
bool DoublyLinkedList<T>::isExistBinarySearch(T searchKey)
{
	Node<T> *tmp = mHead;
	if (mHead == NULL)
	{
		return false;
	}
	else
	{
		int first = 0,
			last = mCount - 1,
			middle;

		while(first <= last)
		{
			middle = (first + last)/2;
			if(getData(middle) == searchKey)
			{
				return true;
			}
			else if(getData(middle) > searchKey)
			{
				last = middle - 1;
			}
			else
			{
				first = middle + 1;
			}
		}
		
		return false;
		
	}
}

/*      Pre:  The dummy node is instantiated and the searchkey is provided
*     Post:  If the given searchKey exists in the doubly linked list, it is
*            removed from the list
*  Purpose:  To remove a given value from the doubly linked list
******************************************************************************/
template <typename T>
bool DoublyLinkedList<T>::remove(T searchKey)
{
	Node<T> *toBeDeleted;
	
	if (mCount == 0 || !isExist(searchKey))
	{
		return false;
	}
	else
	{
		if (searchKey == mHead->mData)
		{
			toBeDeleted = mHead;
			if(mHead->mNext != NULL)
			{
				mHead = mHead->mNext;
				toBeDeleted->mNext = NULL;
				mHead->mPrevious = NULL;
			}
			delete toBeDeleted;
		}
		else if(searchKey == mTail->mData)
		{
			toBeDeleted = mTail;
			mTail->mPrevious->mNext = NULL;
			mTail = mTail->mPrevious;
			toBeDeleted->mPrevious = NULL;
			delete toBeDeleted;
		}
		else
		{
			toBeDeleted = mHead;
			while(toBeDeleted!= NULL && toBeDeleted->mData!= searchKey)
			{
				toBeDeleted = toBeDeleted->mNext;
			}
			
			toBeDeleted->mPrevious->mNext = toBeDeleted->mNext;
			toBeDeleted->mNext->mPrevious = toBeDeleted->mPrevious;

			toBeDeleted->mNext = NULL;
			toBeDeleted->mPrevious = NULL;

			delete toBeDeleted;
			
		}
		mCount--;
		return true;
	}

}


/*     Pre:  The dummy node is instantiated and the index is provided
*     Post:  If the given index exists in the doubly linked list,
*            removed it from the list, and return the revomed data.
		     return false/0 if index is out of interval
*  Purpose:  To remove a given value from the doubly linked list
******************************************************************************/
template <typename T>
T DoublyLinkedList<T>::removeAt(int index)
{
	if(index < mCount  && index >= 0 )
	{
		Node<T>* toBeDeleted;
		T tempData;

		if (index == 0)
		{
			toBeDeleted = mHead;
			
			if(mHead->mNext != NULL)
			{
				mHead = mHead->mNext;
				toBeDeleted->mNext = NULL;
				mHead->mPrevious = NULL;
				
			}
			tempData = toBeDeleted->mData;
			
			delete toBeDeleted;
			mCount--;
			return tempData;

		}
		else if(index == mCount - 1)
		{
			toBeDeleted = mTail;
			mTail->mPrevious->mNext = NULL;
			mTail = mTail->mPrevious;
			toBeDeleted->mPrevious = NULL;

			tempData = toBeDeleted->mData;

			delete toBeDeleted;
			mCount--;
			return tempData;
		}
		else
		{
			toBeDeleted = mHead;
			for(int i = 0; i < index; i++)
			{
				toBeDeleted = toBeDeleted->mNext;
			}
			toBeDeleted->mPrevious->mNext = toBeDeleted->mNext;
			toBeDeleted->mNext->mPrevious = toBeDeleted->mPrevious;
		
			toBeDeleted->mPrevious = NULL;
			toBeDeleted->mNext = NULL;

			tempData = toBeDeleted->mData;

			delete toBeDeleted;
			mCount--;
			return tempData;
		}
		
	}

	return false;
}

