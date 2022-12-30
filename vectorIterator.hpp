#ifndef VITERATOR_CPP
#define VITERATOR_CPP

# include <iostream>
# include <iterator>
#include <cstddef>

namespace ft
{
	template <class T>
	class vectorIterator : public std::iterator<std::random_access_iterator_tag, T>
	{
		private:
			T* ptr;
		public:
			typedef	std::random_access_iterator_tag iterator_category;
			typedef T								value_type;
			typedef ptrdiff_t 						difference_type;
			typedef T*								pointer;
			typedef T& 								reference;

			// _________________/ Constructors \_________________ //

			vectorIterator(T* s = NULL){

				ptr = s;
			};

			vectorIterator(const vectorIterator& x) {

				ptr = x.ptr;
			};

			vectorIterator& operator = (const vectorIterator& x) {

				ptr = x.ptr;
				return *this;
			};

		// _________________/ Destructor \_________________ //

			~vectorIterator() {

				ptr = NULL;
			};


		bool operator == (const vectorIterator& x) const{
			
			return (ptr == x.ptr);
		};

		bool operator != (const vectorIterator& x) const{

			return  (ptr != x.ptr);
		};

		reference operator * () {
			
			return *ptr;
		}

		vectorIterator& operator ++ () {

			ptr++;
			return *this;
		}

		vectorIterator operator++(int)
		{
			vectorIterator tmp = *this;
			ptr++;
			return tmp;
		}

		vectorIterator &operator--()
		{

			ptr--;
			return *this;
		}

		vectorIterator operator--(int)
		{
			vectorIterator tmp = *this;
			ptr++;
			return tmp;
		}

		vectorIterator operator + (difference_type a) {
			
			vectorIterator tmp = *this;
			tmp.ptr += a;
			return tmp;
		}

		vectorIterator operator-(difference_type a)
		{
			vectorIterator tmp = *this;
			tmp.ptr -= a;
			return tmp;
		}

		long int operator - (vectorIterator& x) {

			return (ptr - x.ptr);
		}

		bool operator < (const vectorIterator& x) const{

			return (ptr < x.ptr);
		}

		bool operator > (const vectorIterator &x) const 
		{

			return (ptr > x.ptr);
		}

		bool operator <= (const vectorIterator &x) const
		{

			return (ptr <= x.ptr);
		}

		bool operator >= (const vectorIterator &x) const
		{

			return (ptr >= x.ptr);
		}

		void operator += (difference_type a) {

			ptr += a;
		}
		void operator -= (difference_type a)
		{

			ptr -= a;
		}

		reference operator [] (size_t i) {

			return ptr[i];
		}
	};
} 


# endif