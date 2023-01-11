/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:37:28 by mmardi            #+#    #+#             */
/*   Updated: 2023/01/11 17:05:13 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDB_HPP
#define RDB_HPP

template<class T>
struct Node {
  T data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
  Node() :  parent(NULL) ,left(NULL) ,right(NULL),  color(1) {}
  Node(const T &val) : data(val), parent(NULL) ,left(NULL) ,right(NULL),  color(1) {}
};

template <class T> 
class RedBlackTree {
  public:
    typedef Node<T>* _Node;
    _Node root;
  private:
    _Node _nil;

    void leftRotate(_Node x)
    {
      _Node y = x->right;
      x->right = y->left;
      if (y->left != _nil)
        y->left->parent = x;
      y->parent = x->parent;
      if (x->parent == nullptr)
        this->root = y;
      else if (x == x->parent->left)
        x->parent->left = y;
      else
        x->parent->right = y;
      y->left = x;
      x->parent = y;
    }

    void Transplant(_Node d_node, _Node node) {

      if (!d_node->parent)
        this->root = node;
      else if (d_node == d_node->parent->right)
        d_node->parent->right = node;
      else
        d_node->parent->left = node;
      node->parent = d_node->parent;     
    }

    _Node getMinNode(_Node x) {
      _Node node = x;
      while(node->left != _nil)
        node = node->left;
      return node;
    }

    void  rightRotate(_Node x)
    {
      _Node y = x->left;
      x->left = y->right;
      if (y->right != _nil)
        y->right->parent = x;
      y->parent = x->parent;
      if (x->parent == NULL)
        this->root = y;
      else if (x == x->parent->right)
        x->parent->right = y;
      else
        x->parent->left = y;
      y->right = x;
      x->parent = y;
    }
  void inserHandler(_Node node) {
    if (node->parent->color == 0)
      return;
    while (node->color == 1 && node->parent->color == 1) {
      if (node->parent == node->parent->parent->left) {
        if (node->parent->parent->right->color == 1) {

          node->parent->color = 0;
          node->parent->parent->right->color = 0;
          node->parent->parent->color = 1;
          node = node->parent->parent;
        }
        else {
          if (node == node->parent->right) {
            node = node->parent;
            leftRotate(node);
          }
          node->parent->color = 0;
          node->parent->parent->color = 1;
          rightRotate(node->parent->parent);
        }
      }
      else {
        if (node->parent->parent->left->color == 1) {
          node->parent->color = 0;
          node->parent->parent->left->color = 0;
          node->parent->parent->color = 1;
          node = node->parent->parent;
        }
         else {
          if (node == node->parent->right) {
            node = node->parent;
            rightRotate(node);
          }
          node->parent->color = 0;
          node->parent->parent->color = 1;
          leftRotate(node->parent->parent);
        }
      }
      if (node == this->root) {
        break;
      }
    }
    this->root->color = 0;
  }


  void deleteHandler(_Node x) {
    _Node s;
    while(x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->parent->color = 1;
          s->color = 0;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        }
        else {
          if (s->right->color == 0) {
            s->color = 1;
            s->left->color = 0;
            rightRotate(s);
            s = x->parent->right;        
          }
          s->color = x->parent->color;
          s->right->color = 0;
          x->parent->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      }
      else {
        s = x->parent->left;
        if (s->color == 1)
        {
          s->parent->color = 1;
          s->color = 0;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->left->color == 0 && s->right->color == 0)
        {
          s->color = 1;
          x = x->parent;
        }
        else
        {
          if (s->left->color == 0)
          {
            s->color = 1;
            s->right->color = 0;
            leftRotate(s);
            s = x->parent->left;
          }
          s->color = x->parent->color;
          s->left->color = 0;
          x->parent->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }
    
  public:
    RedBlackTree() {
      _nil = new Node<T>;
      _nil->color = 0;
      root = nullptr;
    }
    
    void insert(_Node newNode) {
      newNode->left = _nil;
      newNode->right = _nil;
      if (!root) {
        this->root = newNode;
        this->root->color = 0;
      }
      else {
        _Node tmp = this->root;
        _Node parent;
        bool r;
        while(tmp != _nil) {
          parent = tmp;
          if (tmp->data <= newNode->data) {
            r = true; 
            tmp = tmp->right;
          }
          else  {
            r = false; 
            tmp = tmp->left;
          }
        }
        newNode->parent = parent;
        if (r)
          parent->right = newNode;
        else
          parent->left = newNode;
        
        inserHandler(newNode);  
      }
    }

    void deleteNode(_Node d_node) {
      
      _Node x = this->root;
      _Node toFix;
      _Node min;
      while(x !=  d_node)
      {
        if (d_node->data >= x->data)
          x = x->right;
        else
          x = x->left;
        if (x == _nil) {
          std::cout << "node not found\n";
          return;
        }
      }
      int o_color = x->color;
      if (x->left == _nil) {
        toFix = x->right;
        Transplant(x, x->right);
      }
      else if (x->right == _nil) {
        toFix = x->left;
        Transplant(x, x->left);
      }
      else {
        min = getMinNode(x->right);
        o_color = min->color;
        toFix = min->right;
        if (min->parent == x)
          toFix->parent = min;
        else {
          
          Transplant(min,min->right);
          min->right = x->right;
          min->right->parent = min;
        }
        Transplant(x,min);
        min->left = x->left;
        min->left->parent = min;
        min->color = x->color;
      }
      delete x;
      if (o_color == 0)
        deleteHandler(toFix);
    }
};
#endif