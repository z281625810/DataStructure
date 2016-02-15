#ifndef _AVL_H
#define _AVL_H

#include <iostream>
#include <algorithm>
#include "queue.h"

using namespace std;

template <typename T>
class AVL
{
   private:
      template <typename T>
      struct Node
      {
         T       mData;
         int     mHeight;
         Node<T> *mLeft, *mRight;

         /*      Pre:  None
          *     Post:  This object is initialized using default values
          *  Purpose:  To intialize date object
          *************************************************************************/
         Node()
         {
            mData = T();
            mHeight = 1;
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
            mHeight = 1;
            mLeft = NULL;
            mRight = NULL;
         }


         Node(T data, Node<T> *left, Node<T> *right)
         {
            mData = data;
            mHeight = 1;
            mLeft = left;
            mRight = right;
         }
      };

      Node<T> *mRootNode;

      AVL(T data, Node<T> *left, Node<T> *right);

      bool bfs(Queue<Node<T>*> *queue, const T &searchKey);
      void destroySubtree(Node<T> *node);
      bool dfs(Node<T> *node, const T &searchKey);
      void displayInOrder(Node<T> *node);
      void displayPreOrder(Node<T> *node);
      void displayPostOrder(Node<T> *node);
      void displayTree(Node<T> *node, int tab);
      int  getBalance(Node<T> *node);
      int  getHeight(Node<T> *node);
      void getHeight(Node<T> *node, int &max, int layer);
      void insert(Node<T> *&node, const T &data);
      void leavesCount(Node<T> *node, int &count);
      int  maxHeight(Node<T> *node1, Node<T> *node2);
      void nodesCount(Node<T> *node, int &count);
      void makeDeletion(Node<T> *&node);
      void remove(Node<T> *&node, const T &searchKey);
      void rotateLeft(Node<T> *&node);
      void rotateLeftRight(Node<T> *&node);
      void rotateRight(Node<T> *&node);
      void rotateRightLeft(Node<T> *&node);


   public:
      AVL();
      ~AVL();

      bool bfs(T searchKey);
      bool dfs(T searchKey);
      int  getHeight();
      void insert(T data);
      bool isEmpty();
      bool isExists(T searchKey);
      int  leavesCount();
      int  nodesCount();
      void remove(T searchKey);
      void printPath(T searchKey);
      void showInOrder();
      void showPreOrder();
      void showPostOrder();
      void showTree();
};


template <typename T>
AVL<T>::AVL()
{
   mRootNode = NULL;
}


template <typename T>
AVL<T>::AVL(T data, Node<T> *left = NULL, Node<T> *right = NULL)
{
   Node<T> *newNode;

   newNode = new Node(data, left, right);
   newNode->mHeight = maxHeight(left, right) + 1;
   if (newNode != NULL)
      mRootNode = newNode;
}


template <typename T>
AVL<T>::~AVL()
{
   destroySubtree(mRootNode);
}


template <typename T>
bool AVL<T>::bfs(T searchKey)
{
   bool found = false;
   Queue<Node<T>*> *queue = new Queue<Node<T>*>;

   if (!isEmpty())
   {
      queue->enqueue(mRootNode);
      found = bfs(queue, searchKey);
   }

   delete queue;

   return found;
}


template <typename T>
bool AVL<T>::bfs(Queue<Node<T>*> *queue, const T &searchKey)
{
   bool found = false;
   Node<T>* tmp;

   if (!queue->isEmpty())
   {
      tmp = queue->dequeue();

cout << "seeing:  " << tmp->mData << endl;

      if (tmp->mData == searchKey)
         found = true;
      else
      {
         if (tmp->mLeft != NULL)
            queue->enqueue(tmp->mLeft);

         if (tmp->mRight != NULL)
            queue->enqueue(tmp->mRight);

         found = bfs(queue, searchKey);
      }
   }

   return found;
}


template <typename T>
void AVL<T>::destroySubtree(Node<T> *node)
{
   if (node == NULL)
      return;

   destroySubtree(node->mLeft);
   destroySubtree(node->mRight);

   // Delete the node at the root.
   delete node;
}


template <typename T>
bool AVL<T>::dfs(T searchKey)
{
   bool found = false;

   if (!isEmpty())
      found = dfs(mRootNode, searchKey);

   return found;
}


template <typename T>
bool AVL<T>::dfs(Node<T> *node, const T &searchKey)
{
   bool found = false;

   if (node != NULL)
   {
cout << "seeing:  " << node->mData << endl;

      if (node->mData == searchKey)
         found = true;
      else
      {
         found = dfs(node->mLeft, searchKey);

         if (!found)
            found = dfs(node->mRight, searchKey);
      }
   }

   return found;
}


template <typename T>
void AVL<T>::displayInOrder(Node<T> *node)
{
   if (node != NULL)
   {
      displayInOrder(node->mLeft);
      cout << node->mData << "  ";
      displayInOrder(node->mRight);
   }
}


template <typename T>
void AVL<T>::displayPreOrder(Node<T> *node)
{
   if (node != NULL)
   {
      cout << node->mData << "  ";
      displayPreOrder(node->mLeft);		
      displayPreOrder(node->mRight);
   }
}


template <typename T>
void AVL<T>::displayPostOrder(Node<T> *node)
{
   if (node != NULL)
   {
      displayPostOrder(node->mLeft);		
      displayPostOrder(node->mRight);
      cout << node->mData << "  ";
   }
}


template <typename T>
void AVL<T>::displayTree(Node<T> *node, int tab)
{
   int i;

   if (node != NULL)
   {
      for (i = 0; i < tab; i++)
         cout << "  ";

      cout << node->mData << "(H: " << node->mHeight << ", B:  " << getBalance(node) << ")\n";

      displayTree(node->mLeft, tab + 1);
      displayTree(node->mRight, tab + 1);
   }
}


// Balance is defined as H(R) - H(L)
template <typename T>
int AVL<T>::getBalance(Node<T> *node)
{
   if (node == NULL)
      return 0;
   else
      return getHeight(node->mRight) - getHeight(node->mLeft);
}


template <typename T>
int AVL<T>::getHeight()
{
   int max = 0;

   getHeight(mRootNode, max, 0);
   return max;
}


template <typename T>
int AVL<T>::getHeight(Node<T> *node)
{
   if (node == NULL)
      return 0;
   else
      return node->mHeight;
}


template <typename T>
void AVL<T>::getHeight(Node<T> *node, int &max, int layer)
{
   if (node == NULL)
      return;

   if (node->mLeft == NULL && node->mRight == NULL)
   {
      if (layer > max)
         max = layer;
   }
   else
   {
      layer++;
      getHeight(node->mLeft, max, layer);
      getHeight(node->mRight, max, layer);
   }
}


template <typename T>
void AVL<T>::insert(T data)
{
   insert(mRootNode, data);
}


template <typename T>
void AVL<T>::insert(Node<T> *&node, const T &data)
{
   // If the tree is empty, make a new node and make it 
   // the root of the tree.
   if (node == NULL)
   { 
      node = new Node<T>(data);
      return;
   }
		
   // If num is already in tree: return.
   if (node->mData == data)
      return;

   // The tree is not empty: insert the new node into the
   // left or right subtree.
   if (data < node->mData)
   {
      insert(node->mLeft, data);
      if (getBalance(node) == -2)
      {
         //if (data < node->mLeft->mData)
         if (getBalance(node->mLeft) == -1)
            rotateRight(node);
         else
            rotateLeftRight(node);
      }
   }
   else
   {
      insert(node->mRight, data);
      if (getBalance(node) == 2)
      {
         //if (data > node->mRight->mData)
         if (getBalance(node->mRight) == 1)
            rotateLeft(node);
         else
            rotateRightLeft(node);
      }
   }

   node->mHeight = maxHeight(node->mLeft, node->mRight) + 1;
}


template <typename T>
bool AVL<T>::isEmpty()
{
   return (mRootNode == NULL);
}


template <typename T>
bool AVL<T>::isExists(T searchKey)
{
   Node<T> *tmp = mRootNode;

   while (tmp != NULL)
   {
      if (tmp->mData == searchKey)
         return true;
      else if (tmp->mData > searchKey)
         tmp = tmp->mLeft;
      else
         tmp = tmp->mRight;
   }
   return false;
}


template <typename T>
int AVL<T>::leavesCount()
{
   int count = 0;

   leavesCount(mRootNode, count);
   return count;
}


template <typename T>
void AVL<T>::leavesCount(Node<T> *node, int &count)
{
   if (node == NULL)
      return;

   if (node->mLeft == NULL && node->mRight == NULL)
      count++;
   else
   {
      leavesCount(node->mLeft, count);
      leavesCount(node->mRight, count);
   }
}


template <typename T>
void AVL<T>::makeDeletion(Node<T> *&node)
{
   // Used to hold node that will be deleted.
   Node<T> *nodeToDelete = node, *oneAbove; 
	
   // Used to locate the  point where the 
   // left subtree is attached.
   Node<T> *attachPoint;          
			
   // Replace tree with its left subtree.	
   if (node->mRight == NULL)
   {
      node = node->mLeft;
   }    
   // Replace tree with its right subtree.        
   else if (node->mLeft == NULL)   	
   {
      node = node->mRight;
   }  	
   else
   {
      // Move to right subtree.
      attachPoint = node->mRight;
      oneAbove = NULL;

      // Locate the smallest node in the right subtree
      // by moving as far to the left as possible.
      while (attachPoint->mLeft != NULL)
      {
         oneAbove = attachPoint;
         attachPoint = attachPoint->mLeft;
      }

      // Attach the left subtree of the original tree
      // as the left subtree of the smallest node 
      // in the right subtree.
      attachPoint->mLeft = node->mLeft;

      if (attachPoint != node->mRight)
         attachPoint->mRight = node->mRight;

      if (oneAbove != NULL)
         oneAbove->mLeft = NULL;

      // Replace the original tree with its right subtree.
      node = attachPoint;       
   }   

   // Delete root of original tree
   delete nodeToDelete;
}


template <typename T>
int AVL<T>::maxHeight(Node<T> *node1, Node<T> *node2)
{
   int heightNode1, heightNode2;

   if (node1 == NULL)
      heightNode1 = 0;
   else
      heightNode1 = node1->mHeight;

   if (node2 == NULL)
      heightNode2 = 0;
   else
      heightNode2 = node2->mHeight;

   if (heightNode1 >= heightNode2)
      return heightNode1;
   else
      return heightNode2;
}


template <typename T>
int AVL<T>::nodesCount()
{
   int count = 0;

   nodesCount(mRootNode, count);
   return count;
}


template <typename T>
void AVL<T>::nodesCount(Node<T> *node, int &count)
{
   if (node != NULL)
   {
      nodesCount(node->mLeft, count);
      nodesCount(node->mRight, count);
      count++;
   }
}


template <typename T>
void AVL<T>::printPath(T searchKey)
{
   Node<T> *tmp = mRootNode;
   Queue<T> queue;
   bool     found = false;

   while (tmp != NULL && !found)
   {
      queue.enqueue(tmp->mData);

      if (tmp->mData == searchKey)
         found = true;
      else if (tmp->mData > searchKey)
         tmp = tmp->mLeft;
      else
         tmp = tmp->mRight;
   }
	
   if (!found)
      cout << searchKey << " is not found in the list\n";
   else
   {
      cout << "Path: "; 
      queue.display();
      cout << endl;
   }
}


template <typename T>
void AVL<T>::remove(Node<T> *&node, const T &searchKey)
{
   if (node == NULL)
      return;
   else if (node->mData > searchKey)
   {
      remove(node->mLeft, searchKey);

      if (getBalance(node) == 2)
      {
         if (getBalance(node->mLeft) <= 1)
            rotateLeft(node);
         else
            rotateRightLeft(node);
      }
   }
   else if (node->mData < searchKey)
   {
      remove(node->mRight, searchKey);

      if (getBalance(node) == -2)
      {
         if (getBalance(node->mRight) >= -1)
            rotateRight(node);
         else
            rotateLeftRight(node);
      }
   }
   else
   {
      // We have found the node to delete.
      makeDeletion(node);

      if (getBalance(node) == 2)
      {
         if (getBalance(node->mLeft) <= 1)
            rotateLeft(node);
         else
            rotateRightLeft(node);
      }

      else if (getBalance(node) == -2)
      {
         if (getBalance(node->mRight) >= -1)
            rotateRight(node);
         else
            rotateLeftRight(node);
      }
   }

   if (node != NULL)
      node->mHeight = maxHeight(node->mLeft, node->mRight) + 1;
}


template <typename T>
void AVL<T>::remove(T searchKey)
{
   remove(mRootNode, searchKey);
}


template <typename T>
void AVL<T>::showInOrder()
{
   displayInOrder(mRootNode);
}


template <typename T>
void AVL<T>::showPreOrder()
{
   displayPreOrder(mRootNode); 
}


template <typename T>
void AVL<T>::showPostOrder()
{
   displayPostOrder(mRootNode);
}


template <typename T>
void AVL<T>::showTree()
{
   displayTree(mRootNode, 0);
}


template <typename T>
void AVL<T>::rotateLeft( Node<T> *&node)
{
   Node<T> *tmp = node->mRight;

   node->mRight = tmp->mLeft;
   tmp->mLeft = node;
   node->mHeight = maxHeight(node->mLeft, node->mRight) + 1;
   tmp->mHeight = max(getHeight(tmp->mRight), node->mHeight) + 1;
   node = tmp;
}


template <typename T>
void AVL<T>::rotateLeftRight( Node<T> *&node)
{
   rotateLeft(node->mLeft);
   rotateRight(node);
}


template <typename T>
void AVL<T>::rotateRight( Node<T> *&node)
{
   Node<T> *tmp = node->mLeft;

   node->mLeft = tmp->mRight;
   tmp->mRight = node;
   node->mHeight = maxHeight(node->mLeft, node->mRight) + 1;
   tmp->mHeight = max(getHeight(tmp->mLeft), node->mHeight) + 1;
   node = tmp;
}


template <typename T>
void AVL<T>::rotateRightLeft(Node<T> *&node)
{
   rotateRight(node->mRight);
   rotateLeft(node);
}


#endif