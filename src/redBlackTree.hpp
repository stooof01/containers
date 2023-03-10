/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:37:28 by mmardi            #+#    #+#             */
/*   Updated: 2023/03/01 17:02:02 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RDB_HPP
#define RDB_HPP
 
# include <iterator>
# include <memory>
# include "../utility/pair.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../utility/equal.hpp"


namespace  ft {
  
  template <class T, class Node>
  class rbt_iterator : public std::iterator<T, std::bidirectional_iterator_tag> {
    public:
      typedef T									value_type;
      typedef Node							_Node;
  		typedef std::ptrdiff_t 		difference_type;
  		typedef T*								pointer;
  		typedef const T*					const_pointer;
  		typedef T& 					      reference;
  		typedef const T& 					const_reference;
      private:
        pointer ptr;
        _Node node;
        _Node nil;
        _Node root;
      public:
        rbt_iterator(){}
        rbt_iterator(const rbt_iterator& x) {
          node = x.node; 
          nil = x.nil;
          root = x.root;
          ptr = &node->data;
        }
        rbt_iterator& operator = (const rbt_iterator& x) {
          node = x.node; 
          nil = x.nil; 
          root = x.root;
          ptr = &node->data;
          return *this; 
        }
        rbt_iterator(_Node _node, _Node _nil, _Node _root) {
          node = _node; 
          nil = _nil;
          root = _root;
          ptr = &node->data; 
        }
        bool operator == (const rbt_iterator& x) const { return ptr == x.ptr; }
        bool operator != (const rbt_iterator& x) const { return ptr != x.ptr; }
        reference operator * () { return *ptr; }
        const_reference operator * () const{ return *ptr; }
        pointer operator -> () {  return &(operator*()); };
        const_pointer operator -> () const {  return &(operator*()); };
        void operator = (const value_type& x) { ptr = &x; }
        rbt_iterator& operator ++ () { 
          node =  getSuccessor(node);
          ptr = &node->data;
          return *this;
        }
        rbt_iterator operator ++ (int) { 
         rbt_iterator tmp(*this);
         ++(*this);
          return tmp;
        }
  
        rbt_iterator& operator -- () { 
          node =  getPredesuccessor(node);
          ptr = &node->data;
          return *this;
        }
  
        rbt_iterator operator -- (int) { 
         rbt_iterator tmp(*this);
         --(*this);
          return tmp;
        }

        int getColor() {
        return node->color;
      }
      private:
        _Node getMinNode(_Node x) {
          _Node node = x;
          while(node->left != nil) node = node->left;
          return node;
        }
    
        _Node getMaxNode(_Node x) {
          _Node node = x;
          while(node->right != nil) node = node->right;
          return node;
        }
      
        _Node getSuccessor(_Node x) {
          if ( x == nil) 
            return getMaxNode(root);
            if (x->right != nil) {
              return getMinNode(x->right);
            }
    
            _Node y = x->parent;
            while (y != NULL && x == y->right) {
               x = y;
               y = x->parent; 
            }
            
            if (!y)
              return nil;
            return y;
        }
      
       _Node getPredesuccessor(_Node x) {
        
        if ( x == nil) 
            return getMaxNode(root);
          if (x->left != nil) {
            return getMaxNode(x->left);
          }
  
          _Node y = x->parent;
          while (y != NULL && x == y->left) {
             x = y;
             y = x->parent; 
          }

          if (!y)
            return nil;
          return y;
      }
    public:
      void printElement() {
        std::cout << ptr->first << " color: " << node->color << std::endl;
      }
      
  };
  
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
  
  template <class T, class Comp, class Alloc> 
  class RedBlackTree {
    public:
      typedef T                             value_type;
      typedef Node<value_type>*             _Node;
      typedef Node<value_type>              node;
      typedef  typename Alloc::template rebind<node>::other       allocator_type;
      typedef ft::rbt_iterator<value_type,_Node>        iterator;
      typedef const ft::rbt_iterator<value_type,_Node> const_iterator;
      typedef Comp                        comp;
      typedef ft::reverse_iterator<iterator>                          reverse_iterator;
      typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;
    private:
      _Node _nil;
      _Node root;
      comp _comp;
      allocator_type _alloc;
      
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
  
      _Node getMinNode(_Node x) const {
        _Node node = x;
        if (!x)
          return _nil;
        if (x == _nil)
          return x;
        while(node->left != _nil )
            node = node->left;
        return node;
      }

      _Node getMaxNode(_Node x) const {
        _Node node = x;
        if (x == _nil)
          return x;
        while(node->right != _nil)
          node = node->right;
        return node;
      }
      void  rightRotate(_Node x) {
        _Node y = x->left;
        x->left = y->right;
        if (y->right != _nil) {
          y->right->parent = x;
        }
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
    void insertHandler(_Node node) {
    
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
            if (node == node->parent->left) {
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
        _nil = _alloc.allocate(1);
        _nil->color = 0;
        _nil->left = NULL;
        _nil->right = NULL;
        root = NULL;
      }
      ~RedBlackTree() {
        _alloc.deallocate(_nil, 1);
      }
      ft::pair<iterator,bool> 
                insert(const value_type& t) {
                  
        _Node newNode = _alloc.allocate(1); 
        _alloc.construct(newNode,node(t));
        newNode->parent = NULL;
        newNode->left = _nil;
        newNode->right = _nil;
        
        if (!root || root == _nil) {
          this->root = newNode;
          this->root->color = 0;
        }
        else {
          _Node tmp = this->root;
          _Node parent;
          bool r;
          while(tmp != _nil) {
            parent = tmp;
            if (!_comp(tmp->data, newNode->data) && !_comp(newNode->data, tmp->data)) {
              _alloc.destroy(newNode);
              _alloc.deallocate(newNode,1);
              return ft::make_pair(iterator(tmp,_nil,root), false);
            }
            else if (_comp(newNode->data, tmp->data))
            {
              r = false; 
              tmp = tmp->left;
            }
            else {
              r = true; 
              tmp = tmp->right;
            }
          }
          newNode->parent = parent;
          if (r)
            parent->right = newNode;
          else
            parent->left = newNode;
          
          insertHandler(newNode);
        }
          return ft::make_pair(iterator(newNode,_nil,root), true);
      }
  
      void deleteNode(_Node d_node) {
        
        _Node x = this->root;
        _Node toFix;
        _Node min;
        while(x !=  d_node)
        {
          if (_comp(d_node->data, x->data))
            x = x->left;
          else
            x = x->right;
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
        _alloc.deallocate(x,1);
        if (o_color == 0)
          deleteHandler(toFix);
      }
      iterator begin(){
        
        return iterator(getMinNode(root), _nil,root);
      }

      const_iterator begin() const {   
        return const_iterator(getMinNode(root), _nil,root);
      }
      iterator end(){
        return  iterator(_nil,_nil,root);
      }
      const_iterator end() const{
          return iterator(_nil,_nil,root);
      }

      _Node findNode(value_type k) const {
        _Node x = root;
        while(1)
        {
          if (x->data == k)
            return x ;
          if (_comp(k, x->data))
            x = x->left;
          else 
            x = x->right;
          if (x == _nil) 
            return NULL;
        }
        return x;
      }
      size_t maxSize() const {
        return _alloc.max_size();
      }

      
  };
}


#endif