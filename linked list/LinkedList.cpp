/* ***  Author:  Feng Sun
*  Last Update:  September 10, 2014
*        Class:  CSI-281
*     Filename:  LinkedList.cpp
*
*  Description:
*      This is the template linked list implementations.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#include "LinkedList.h"

/*      Pre:  None
*     Post:  This object is initialized using the default
*  Purpose:  To initialize date object
*****************************************************************************/
template <typename T>
LinkedList<T>::LinkedList()
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
LinkedList<T>::~LinkedList()
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
int LinkedList<T>::getCount()
{
	return mCount;
}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  The data in the specified index is returned to the caller
*  Purpose:  To retrieve the specified nodes in the list
*****************************************************************************/
template <typename T>
T LinkedList<T>::getData(int index)
{
	if(mCount > index && index >= 0)
	{
		Node<T> *tmp;
		tmp = mHead;
		int tempIndex = 0;
		while (tempIndex < index)
		{
			tmp = tmp->mNext;
			tempIndex++;
		}
		return tmp->mData;
	}
	else
	{
		cout << "invalid index" << endl;
		return false;
	}
}


/*      Pre:  The list is instantiated, the index is valid and the data is
*            available
*     Post:  The data in the specified index is updated with the specified
*            data
*  Purpose:  To update the specified nodes in the list
*****************************************************************************/
template <typename T>
void LinkedList<T>::setData(int index, T data)
{
	if(mCount > index  && index >= 0)
	{
		Node<T> *tmp;
		tmp = mHead; 
		int tempIndex = 0;
		while (tempIndex < index)
		{
			tmp = tmp->mNext;
			tempIndex++;
		}
		tmp->mData = data;
	}
	else
	{
		cout << "invalid index" << endl;
		return;
	}
}


/*      Pre:  The list is initiated
*     Post:  All the nodes in the list is deleted
*  Purpose:  To remove all the nodes in the list
*****************************************************************************/
template <typename T>
void LinkedList<T>::clear()
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


/*      Pre:  The list is instantiated
*     Post:  The entire list is displayed on the screen
*  Purpose:  To show the content of the list
*****************************************************************************/
template <typename T>
void LinkedList<T>::display()
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


/*      Pre:  The list is instantiated and the data is available
*     Post:  The data is inserted in ascending order
*  Purpose:  To insert a data into the list in ascending order.  However, if
*            the data already existed in the list, it will not be added again
*****************************************************************************/
template <typename T>
bool LinkedList<T>::insert(T data)
{
	Node<T> *tmp, *oneBefore, *newNode;
	newNode = new Node<T>(data);
	if (newNode == NULL)
		return false;

	if (mHead == NULL)
	{
		mHead = newNode;
		mTail = newNode;
		mCount++;
		return true;
	}

	if (mHead->mData > data)
	{
		newNode->mNext = mHead;
		mHead = newNode;
		mCount++;
		return true;
	}
	else if (mTail->mData < data)
	{
		mTail->mNext = newNode;
		mTail = newNode;
		mCount++;
		return true;
	}
	else
	{
		tmp = mHead;
		oneBefore = mHead;
		while (tmp->mData < data)
		{
			oneBefore = tmp;
			tmp = tmp->mNext;
		}
		if (tmp->mData == data)
		{
			delete newNode;
			newNode = NULL;
			return false;
		}
		
		newNode->mNext = tmp;
		oneBefore->mNext = newNode;
		mCount++;
		return true;
	}

}


/*      Pre:  The list is instantiated
*     Post:  The function returns true is the list is empty; false otherwise
*  Purpose:  To determine if the list is empty
*****************************************************************************/
template <typename T>
bool LinkedList<T>::isEmpty()
{
	if (mHead == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/*      Pre:  The list is instantiated and the searchKey is available
*     Post:  The function returns true if the search key exists in the list;
*            otherwise false
*  Purpose:  To determine if a specific value exists in the list or not
*****************************************************************************/
template <typename T>
bool LinkedList<T>::isExist(T searchKey)
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


/*      Pre:  The list is instantiated and the searchKey is available
*     Post:  If the searchKey exists, removes it from the list and the
*            function returns true; otherwise the function does nothing
*            and returns false
*  Purpose:  To remove a specific value from the list
*****************************************************************************/
template <typename T>
bool LinkedList<T>::remove(T searchKey)
{
	Node<T> *toBeDeleted;
	Node<T>	*tmp;
	tmp = mHead;

	if (tmp == NULL || !isExist(searchKey))
	{
		return false;
	}
	else
	{
		if (searchKey == mHead->mData)
		{
			toBeDeleted = mHead;
			mHead = mHead->mNext;
			toBeDeleted->mNext = NULL;
			delete toBeDeleted;
			mCount--;
			return true;
		}
		else if(searchKey == mTail->mData)
		{
			while(tmp -> mNext != mTail)
			{
				tmp = tmp->mNext;
			}
			toBeDeleted = mTail;
			mTail = tmp;
			mTail->mNext = NULL;
			delete toBeDeleted;
			mCount--;
			return true;
		}
		else
		{
			Node<T> *oneBefore;
			oneBefore = mHead;
			while(tmp!= NULL && tmp->mData!= searchKey)
			{
				oneBefore = tmp;
				tmp = tmp->mNext;
			}
			toBeDeleted = tmp;
			oneBefore->mNext = tmp->mNext;
			toBeDeleted->mNext = NULL;
			delete toBeDeleted;
			mCount--;
			return true;
			
		}
	}

}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  Remove the element in the specified index location and returns
*            its content to the caller.  If the index location is invalid, the
*            function returns the default value
*  Purpose:  To remove an item in the specified index location
*****************************************************************************/
template <typename T>
T LinkedList<T>::removeAt(int index)
{
	Node<T> *toBeDeleted;
	T temp;
	if(mCount - 1 < index || mHead == NULL || index < 0)
	{
		return false;
	}
	else
	{
		if(index == 0)
		{
			toBeDeleted = mHead;
			mHead = mHead->mNext;
			toBeDeleted->mNext = NULL;
			temp = toBeDeleted->mData;
			delete toBeDeleted;
			mCount--;
			return temp;
		}
		else if(index == mCount - 1)
		{
			Node<T> *tmp;
			tmp = mHead;
			while(tmp -> mNext != mTail)
			{
				tmp = tmp->mNext;
			}
			toBeDeleted = mTail;
			mTail = tmp;
			mTail->mNext = NULL;
			temp = toBeDeleted->mData;
			delete toBeDeleted;
			mCount--;
			return temp;
		}
		else
		{
			Node<T> *tmp;
			tmp = mHead;
			Node<T> *oneBefore;
			oneBefore = mHead;
			for(int i = 0; i < index; i++)
			{
				oneBefore = tmp;
				tmp = tmp->mNext;
			}
			toBeDeleted = tmp;
			oneBefore->mNext = tmp->mNext;
			toBeDeleted->mNext = NULL;
			temp = toBeDeleted->mData;
			delete toBeDeleted;
			mCount--;
			return temp;
		}
	}

}


/*      Pre:  The list is instantiated and the index is valid
*     Post:  The data in the specified index is returned to the caller
*  Purpose:  To retrieve the specified nodes in the list using [] operator
*****************************************************************************/
template <typename T>
T LinkedList<T>::operator[](int index)
{
	if (mCount - 1 < index || index < 0 || mHead == NULL)
	{
		return false;
	}
	Node<T> *tmp;
	tmp = mHead;
	int tempIndex = 0;
	while (tempIndex < index)
	{
		tmp = tmp->mNext;
		tempIndex++;
	}
	return tmp->mData;
	
}


/*Pre:  None
* Post:  copy the content of list to this
* Purpose:  To copy the content of list to this
*************************************************************************/
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
	if(mHead != NULL)
	{
		clear();
	}
	Node<T>* tmp = list.mHead;
	while(tmp)
	{
		T obj = tmp->mData;
		insert(obj);
		tmp = tmp->mNext;
	}

	return *this;
}


/*Pre:  None
* Post:  add contents in listTwo to the original list
* Purpose:  add contents in listTwo to the original list
*************************************************************************/
template <typename T>
LinkedList<T>& LinkedList<T>::operator+(LinkedList<T>& listTwo)
{
	for(int i = 0; i < listTwo.getCount(); i++)
	{
		insert(listTwo[i]);
	}
	return *this;
}


/*Pre:  None
* Post:  remove items that are repeated
* Purpose:  To remove same item
*************************************************************************/
template <typename T>
LinkedList<T>& LinkedList<T>::operator-(LinkedList<T>& listTwo)
{
	for(int i = 0; i < mCount; i++)
	{
		for(int y = 0; y < listTwo.getCount(); y++)
		{
			
			if((*this)[i] == listTwo[y])
			{
				removeAt(i);
			}
		}
	}

	return *this;
}