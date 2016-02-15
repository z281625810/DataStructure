/* ***  Author:  Feng Sun
*  Last Update:  November 4, 2014
*        Class:  CSI-281
*     Filename:  BST.h
*
*  Description:
*      This is the implementation and definition of class BST.
*
*  Certification of Authenticity:
*     I certify that this assignment is entirely my own work.
**********************************************************************/

#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <queue>
#include <stack>
#include <iomanip>

using namespace std;

template <typename T>
class BST
{
	private:
      template <typename T>
      struct Node
      {
         T           mData;
         Node<T> *mLeft, *mRight;

         /*      Pre:  None
          *     Post:  This object is initialized using default values
          *  Purpose:  To intialize date object
          *************************************************************************/
         Node()
         {
            mData = T();
            mLeft = NULL;
            mRight = NULL;
         }

         /*      Pre:  None
          *     Post:  This object is initialized using specified data
          *  Purpose:  To intialize date object
          *************************************************************************/
         Node(T data)
         {
            mData = data;
            mLeft = NULL;
            mRight = NULL;
         }

         /*      Pre:  None
          *     Post:  This object is initialized using specified data with the 
          *            specified children attached
          *  Purpose:  To intialize date object
          *************************************************************************/
         Node(T data, Node<T> *left, Node<T> *right)
         {
            mData = data;
            mLeft = left;
            mRight = right;
         }
      };

		Node<T> *mRootNode;

		BST(T data, Node<T> *left, Node<T> *right);
		 int countHeight(Node<T> *&node);
		 int countLeaves(Node<T> *&node);
		 int countNodes(Node<T> *&node);
		void destroySubtree(Node<T> *node);
		void displayInOrder(Node<T> *node);
		void displayPreOrder(Node<T> *node);
		void displayPostOrder(Node<T> *node);
        void displayTree(Node<T> *node, int tab);
		void insert(Node<T> *&node, const T &data);
		void makeDeletion(Node<T> *&node);
		void remove(Node<T> *&node, const T &searchKey);
		
	public:
		BST();
		~BST();
		
		bool bfs(T searchKey);
		bool dfs(T searchKey);
		 int getHeight();
		void insert(T data);
        bool isEmpty();
		bool isExists(T searchKey);
		 int leavesCount();
		 int nodesCount();   
		void printPath(T searchKey);
		void remove(T searchKey);
		void showInOrder();
		void showPreOrder();
		void showPostOrder();
        void showTree();
};



/*      Pre:  None
 *     Post:  This object is initialized using default values
 *  Purpose:  To intialize BST object
 *************************************************************************/
template <typename T>
BST<T>::BST()
{
	mRootNode = NULL;
}


/*      Pre:  none
 *     Post:  This object is initialized
 *  Purpose:  To intialize BST object
 *************************************************************************/
template <typename T>
BST<T>::BST(T data, Node<T> *left = NULL, Node<T> *right = NULL)
{
   Node<T> *newNode;

   newNode = new Node(data, left, right);
   if (newNode != NULL)
	   mRootNode = newNode;
}


/*      Pre:  None
 *     Post:  destroy the object
 *  Purpose:  To destroy BST object
 *************************************************************************/
template <typename T>
BST<T>::~BST()
{
	destroySubtree(mRootNode);
}


/*      Pre:  None
 *     Post:  return the number of height of tree
 *  Purpose:  To count the height of tree
 *************************************************************************/
template <typename T>
int BST<T>::countHeight(Node<T> *&node)
{
	if(node == NULL)
		return 0;

	int leftHeight,
		rightHeight;

	leftHeight = countHeight(node->mLeft);
	rightHeight = countHeight(node->mRight);

	if(leftHeight > rightHeight)
		return leftHeight + 1;
	else
		return rightHeight + 1;
}


/*      Pre:  None
 *     Post:  return the number of leaves of tree
 *  Purpose:  To count the number of leaves of tree
 *************************************************************************/
template <typename T>
int BST<T>::countLeaves(Node<T> *&node)
{
	if(node == NULL)
		return 0;
	if(node->mLeft == NULL && node->mRight == NULL)
		return 1;
	return countLeaves(node->mLeft) + countLeaves(node->mRight);
}


/*      Pre:  None
 *     Post:  return the number nodes of tree
 *  Purpose:  To count the number of nodes of tree
 *************************************************************************/
template <typename T>
int BST<T>::countNodes(Node<T> *&node)
{
	if(node == NULL)
		return 0;
	else
		return countNodes(node->mLeft) + 1 + countNodes(node->mRight);
	
}


/*      Pre:  None
 *     Post:  destroy the subtree
 *  Purpose:  used in destructor
 *************************************************************************/
template <typename T>
void BST<T>::destroySubtree(Node<T> *node)
{
	if(node != NULL)
	{
		if(node->mLeft != NULL)
		{
			destroySubtree(node->mLeft);
		}
		if(node->mRight != NULL)
		{
			destroySubtree(node->mRight);
		}
		delete node;
	}
}


/*      Pre:  none
 *     Post:  display the nodes in inorder, left,root,right
 *  Purpose:  to display in inorder
 *************************************************************************/
template <typename T>
void BST<T>::displayInOrder(Node<T> *node)
{
	if(mRootNode == NULL)
		cout << "The tree is empty";
	
	if(node != NULL)
	{
		displayInOrder(node->mLeft);
		cout << node->mData << " ";
		displayInOrder(node->mRight);
	}
}


/*      Pre:  None
 *     Post:  display in preorder, root, left, right
 *  Purpose:  To display in preorder
 *************************************************************************/
template <typename T>
void BST<T>::displayPreOrder(Node<T> *node)
{
	if(mRootNode == NULL)
		cout << "The tree is empty";
	if(node != NULL)
	{
		cout << node->mData << " ";
		displayPreOrder(node->mLeft);
		displayPreOrder(node->mRight);
	}
}


/*      Pre:  None
 *     Post:  display in postOrder, left, right, root
 *  Purpose:  To display in postOrder
 *************************************************************************/
template <typename T>
void BST<T>::displayPostOrder(Node<T> *node)
{
	if(mRootNode == NULL)
		cout << "The tree is empty";
	if(node!= NULL)
	{
		displayPostOrder(node->mLeft);
		displayPostOrder(node->mRight);
		cout << node->mData << " ";
	}
}


/*      Pre:  tab must be greater or equal to 0
 *     Post:  display the tree hierarchically
 *  Purpose:  To display the tree hierarchically
 *************************************************************************/
template <typename T>
void BST<T>::displayTree(Node<T> *node, int tab)
{
	if(node == NULL)
		return;
	
	if(tab > 0)
		cout << setw(tab);
	cout << node->mData << endl;
	displayTree(node->mLeft,tab + 2);
	displayTree(node->mRight,tab + 2);
	
	
}


/*      Pre:  searchKey must be same type as tree
 *     Post:  return true if key founded, else return false, also print the path
 *  Purpose:  To find the searchkey, and print the path by using bfs
 *************************************************************************/
template <typename T>
bool BST<T>::bfs(T searchKey)
{
	if(mRootNode == NULL)
	{
		cout << "The tree is empty" << endl;
		return false;
	}
		
	queue<Node<T>*> myQueue;
	myQueue.push(mRootNode);
	while(!myQueue.empty())
	{
		Node<T>* temp = myQueue.front();
		myQueue.pop();
		cout << temp->mData << " ";
		if(temp->mData == searchKey)
		{
			cout << endl;
			return true;
		}
		
		if(temp->mLeft != NULL)
			myQueue.push(temp->mLeft);
		if(temp->mRight != NULL)
			myQueue.push(temp->mRight);
	}

	cout << "search key: " << searchKey << " is not found" << endl;
	return false;	
}


/*      Pre:  searchKey must be same type as tree
 *     Post:  return true if key founded, else return false, also print the path
 *  Purpose:  To find the searchkey, and print the path by using dfs
 *************************************************************************/
template <typename T>
bool BST<T>::dfs(T searchKey)
{
	if(mRootNode == NULL)
	{
		cout << "The tree is empty" << endl;
		return false;
	}

	stack<Node<T>*> myStack;
	myStack.push(mRootNode);
	while(!myStack.empty())
	{
		Node<T>* temp = myStack.top();
		cout <<  temp->mData << " ";
		if(temp->mData == searchKey)
		{
			cout << endl;
			return true;
		}

		myStack.pop();
		if(temp->mRight != NULL)
			myStack.push(temp->mRight);
		if(temp->mLeft != NULL)
			myStack.push(temp->mLeft);
	}

	cout << "search key: " << searchKey << " is not found" << endl;
	return false;
	
}


/*      Pre:  none
 *     Post:  return the height of tree
 *  Purpose:  To get the height of tree
 *************************************************************************/
template <typename T>
int BST<T>::getHeight()
{
	if(mRootNode == NULL)
		return 0;
	return countHeight(mRootNode) - 1;
}


/*      Pre:  data must be same type as tree
 *     Post:  insert a new data to tree
 *  Purpose:  To insert a new data to tree
 *************************************************************************/
template <typename T>
void BST<T>::insert(T data)
{
	insert(mRootNode,data);
}


/*      Pre:  data must be same type as tree
 *     Post:  insert a new data to tree
 *  Purpose:  To insert a new data to tree
 *************************************************************************/
template <typename T>
void BST<T>::insert(Node<T> *&node, const T &data)
{
	if (node == NULL)
	{
		node = new Node<T>(data);
		return;
	}
	if (data == node->mData)
	{
		cout << "data: " << data << " already existed" << endl;
		return;
	}
		

	if (data < node->mData)
	{
		insert(node->mLeft, data);
	}
	else
		insert(node->mRight, data);
}


/*      Pre:  none
 *     Post:  return true if it's empty, otherwise return false
 *  Purpose:  To determine the tree whether it's empty or not
 *************************************************************************/
template <typename T>
bool BST<T>::isEmpty()
{
	if(mRootNode == NULL)
		return true;
	else
		return false;
}


/*      Pre:  searchKey must be same type as tree
 *     Post:  return true if key is found, otherwise return false
 *  Purpose:  To find the searchKey whether it's there or not
 *************************************************************************/
template <typename T>
bool BST<T>::isExists(T searchKey)
{
	Node<T>* temp = mRootNode;
	while(temp != NULL)
	{
		if(temp->mData == searchKey)
		{
			return true;
		}
		else if(temp->mData > searchKey)
		{
			temp = temp->mLeft;
		}
		else
		{
			temp = temp->mRight;
		}
	}

	return false;
}


/*      Pre:  None
 *     Post:  return the number of leaves of tree
 *  Purpose:  To count the number of leaves of tree
 *************************************************************************/
template <typename T>
int BST<T>::leavesCount()
{
	return countLeaves(mRootNode);
}


/*      Pre:  None
 *     Post:  return the number nodes of tree
 *  Purpose:  To count the number of nodes of tree
 *************************************************************************/
template <typename T>
int BST<T>::nodesCount()
{
	return countNodes(mRootNode);
}


/*      Pre:  searchKey must be same type as tree
 *     Post:  print the path to searchkey, generate message if it's not found
 *  Purpose:  To print the path to searchkey
 *************************************************************************/
template <typename T>
void BST<T>::printPath(T searchKey)
{
	if(mRootNode == NULL)
	{
		cout << "The tree is empty" << endl;
		return;
	}

	Node<T>* temp = mRootNode;
	Node<T>* oneBefore;
	while(temp != NULL)
	{
		cout << temp->mData << " ";
		if(temp->mData < searchKey)
		{
			oneBefore = temp;
			temp = temp->mRight;
		}
		else if(temp->mData > searchKey)
		{
			oneBefore = temp;
			temp = temp->mLeft;
		}
		else
		{
			cout << endl;
			return;
		}
	}

	if(oneBefore->mData != searchKey)
		cout << "search key: " << searchKey << " is not found" << endl;


}


/*      Pre:  passed in the node that going to be delete
 *     Post:  delete the passed-in node
 *  Purpose:  To delete the passed-in node
 *************************************************************************/
template <typename T>
void BST<T>::makeDeletion(Node<T> *&node)
{
	if(node == NULL)
	{
		return;
	}

	Node<T> *temp = node;
	if(node->mLeft == NULL && node->mRight == NULL) //leaf 
	{
		node = NULL;
		delete temp;
	}
	else if( (node->mLeft == NULL && node->mRight != NULL ) || (node->mLeft != NULL && node->mRight== NULL) ) //one child
	{
		if(node->mRight == NULL)
		{
			node = node->mLeft;
			delete temp;
		}
		else if(node->mLeft == NULL)
		{
			node = node->mRight;
			delete temp;
		}
	}
	else   //two children
	{
		if(node->mRight != NULL)
			temp = node->mRight;
		while(temp->mLeft != NULL)
			temp = temp->mLeft;
		temp->mLeft = node->mLeft;
		temp = node;
		node = node->mRight;
		delete temp;
	}
}


/*      Pre:  searchKey must be same type as tree
 *     Post:  delete the node with searchKey
 *  Purpose:  To delete the node with searchKey
 *************************************************************************/
template <typename T>
void BST<T>::remove(Node<T> *&node, const T &searchKey)
{
	if(!isExists(searchKey))
	{
		cout << "search key: " << searchKey << " doesn't exist" << endl;
		return;
	}
	if(searchKey < node->mData && node != NULL)
		remove(node->mLeft,searchKey);
	else if(searchKey > node->mData && node != NULL)
		remove(node->mRight,searchKey);
	else if(searchKey == node->mData)
	{
		makeDeletion(node);
		cout << "search key: " << searchKey << " is removed successfully" << endl;
	}
}


/*      Pre:  searchKey must be same type as tree
 *     Post:  delete the node with searchKey
 *  Purpose:  To delete the node with searchKey
 *************************************************************************/
template <typename T>
void BST<T>::remove(T searchKey)
{
	remove(mRootNode, searchKey);
}


/*      Pre:  none
 *     Post:  display the nodes in inorder, left,root,right
 *  Purpose:  to display in inorder
 *************************************************************************/
template <typename T>
void BST<T>::showInOrder()
{
	displayInOrder(mRootNode);
	cout << endl;
}


/*      Pre:  None
 *     Post:  display in preorder, root, left, right
 *  Purpose:  To display in preorder
 *************************************************************************/
template <typename T>
void BST<T>::showPreOrder()
{
	displayPreOrder(mRootNode); 
	cout << endl;
}


/*      Pre:  None
 *     Post:  display in postOrder, left, right, root
 *  Purpose:  To display in postOrder
 *************************************************************************/
template <typename T>
void BST<T>::showPostOrder()
{
	displayPostOrder(mRootNode);
	cout << endl;
}


/*      Pre:  none 
 *     Post:  display the tree hierarchically with indentation of 1
 *  Purpose:  To display the tree hierarchically
 *************************************************************************/
template <typename T>
void BST<T>::showTree()
{
	if(mRootNode == NULL)
	{
		cout << "the tree is empty" << endl;
		return;
	}
		

	displayTree(mRootNode,1);

}

#endif