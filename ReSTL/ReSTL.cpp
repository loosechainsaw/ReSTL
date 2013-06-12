#include "stdafx.h"
#include <iostream>

namespace ReSTL{


	struct random_access_iterator_tag{};

	template<typename iterator>
	struct iterator_traits{
		typedef typename iterator::iterator_category iterator_category;
		typedef typename iterator::value_type value_type;
		typedef typename iterator::difference_type difference_type;
		typedef typename iterator::pointer pointer;
		typedef typename iterator::reference reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template<typename T>
	class Array {
	public:
		typedef T* iterator;
		Array() : size_(0)
		{
			elements = nullptr;
		}

		Array(int size) : size_(size)
		{
			elements = new T[size_];
		}

		int const size() const {
			return size_;
		}

		T const & getAt(int index) const
		{
			return elements[index];
		}

		T& getAt(int index)
		{
			return elements[index];
		}

		void setAt(int index, T value)
		{
			elements[size] = value;
		}

		T const & operator[](int index) const{
			return elements[index];
		}

		T& operator[](int index){
			return elements[index];
		}

		iterator begin(){
			return elements;
		}

		iterator end(){
			return elements + size_;
		}
		~Array(){
			delete[] elements;
		}
	private:
		T* elements;
		int size_;
	};

	template<class T>
	class vector{
	public:
		typedef T* iterator;
		vector() : size_(0), capacity_(0)
		{
			elements = nullptr;
		}

		vector(int capacity) : capacity_(capacity), size_(0)
		{
			elements = new T[capacity_];
		}

		void push_back(T const & element){
			allocate();
			elements[size_++] = element;
		}

		int const size() const{
			return size_;
		}

		int const capacity() const{
			return capacity_;
		}

		iterator begin(){
			return elements;
		}

		iterator end(){
			return elements + size_;
		}
		~vector(){
			delete[] elements;
		}
	private:

		void allocate(){

			if(capacity_ == 0){
				auto temp = new T[1];
				elements = temp;
				capacity_ = 1;
				return;
			}

			if(size_ >= capacity_ ){

				auto temp = new T[capacity_ * 2];
				ReSTL::copy(elements, elements + size_, temp);
				delete[] elements;
				elements = temp;
				capacity_ = capacity_ * 2;
			}
		}

		T* elements;
		int size_;
		int capacity_;
	};

	template<typename TIterator>
	void fill(TIterator start, TIterator end, typename iterator_traits<TIterator>::value_type const & value){
		for(;start != end; ++start){
			*start = value;
		}
	}

	template<typename TIterator, typename TFunctor>
	void generate(TIterator start, TIterator end, TFunctor functor){
		for(;start != end; ++start){
			*start = functor();
		}
	}

	template<typename TIterator>
	int count(TIterator start, TIterator end){
		int total = 0;
		for(;start != end; ++start){
			++total;
		}
		return total;
	}

	template<typename TIterator>
	bool all_off(TIterator start, TIterator end, typename iterator_traits<TIterator>::value_type const & value){
		for(;start != end; ++start){
			if(*start != value) return false;
		}
		return true;
	}

	template<typename TIterator>
	bool any_off(TIterator start, TIterator end, typename iterator_traits<TIterator>::value_type const & value){
		for(;start != end; ++start){
			if(*start == value) return true;
		}
		return false;
	}

	template<typename TIterator>
	bool none_off(TIterator start, TIterator end, typename iterator_traits<TIterator>::value_type const & value){
		for(;start != end; ++start){
			if(*start == value) return false;
		}
		return true;
	}

	template<typename TIterator, typename TFunctor>
	void foreach(TIterator start, TIterator end, TFunctor functor){
		for(;start != end; ++start){
			functor(*start);
		}
	}

	template<class TValueType,class TIterator>
	TValueType min_element(TIterator start, TIterator end){
		TValueType min_elem = *start;
		for(;start != end; ++start){
			if(*start < min_elem) 
				min_elem = *start;
		}
		return min_elem;
	}

	template<class TValueType,class TIterator>
	TValueType max_element(TIterator start, TIterator end){
		TValueType max_elem = *start;
		for(;start != end; ++start){
			if(*start > max_elem) 
				max_elem = *start;
		}
		return max_elem;
	}

	template<typename TIterator, typename TFunctor>
	typename iterator_traits<TIterator>::value_type accumulate(TIterator start, TIterator end, typename iterator_traits<TIterator>::value_type const & default_value, TFunctor functor){
		typename iterator_traits<TIterator>::value_type acc = default_value;
		for(;start != end; ++start){
			acc += functor(*start);
		}
		return acc;
	}

	template<typename TInputIterator, typename TOutputIterator>
	void copy(TInputIterator start, TInputIterator end,TOutputIterator dest){
		for(;start != end; ++start, ++dest){
			*dest = *start;
		}
	}

	template<typename TIterator>
	TIterator find(TIterator start, TIterator end, typename iterator_traits<TIterator>::value_type const & value){
		for(;start != end; ++start){
			if(*start == value) return start;
		}
		return end;
	}

	template<class TInputIterator, class TOutputIterator>
	void copy_backwards(TInputIterator start, TInputIterator end, TOutputIterator result)
	{
		for(; end != start; ){
			*(--result) = *--end;
		}
	}

	template<typename TIterator>
	TIterator find_if(TIterator start, TIterator end, typename iterator_traits<TIterator>::value_type const & value){
		for(;start != end; ++start){
			if(*start == value){
				return start;
			}
		}
		return end;
	}

	class type_printer{
	public:

		template<class T>
		static void print(){
			using namespace std;
			cout << "Real typename of the type parameter is: " << typeid(T).name() << endl;
		}
	};

	template<class A, class B>
	struct is_same{
		static const bool value = false;
	};

	template<class A>
	struct is_same<A,A>{
		static const bool value = true;
	};
}


int main()
{
	using namespace std;
	ReSTL::Array<int> array(5);
	ReSTL::Array<float> array2(5);
	ReSTL::type_printer::print<decltype(array)>();
	ReSTL::type_printer::print<decltype(array2)>();

	cout << "The class instantiations ReSTL::Array<int> array(5) = ReSTL::Array<float> array(5) are the same is: " << boolalpha << ReSTL::is_same<ReSTL::Array<int>,ReSTL::Array<float>>::value << endl;
	cout << "The class instantiations ReSTL::Array<int> array(5) = ReSTL::Array<int> array(5) are the same is: " << boolalpha << ReSTL::is_same<ReSTL::Array<int>,ReSTL::Array<int>>::value << endl;

	ReSTL::fill(array.begin(), array.end(), 3);

	cout << "The vector<int> instance has all values equal to 3: " << boolalpha << ReSTL::all_off(array.begin(), array.end(),3) << endl;

	int counter = 0;

	ReSTL::generate(array.begin(), array.end(), [&counter](){
		return ++counter;
	});

	ReSTL::copy(array.begin(), array.end(), array2.begin());

	ReSTL::foreach(array2.begin(), array2.end(), [](float value) { cout << value << endl; });

	cout << "The vector<int> instance has " << ReSTL::count(array.begin(), array.end()) << " elements." <<endl;
	cout << "The vector<int> instance has a min element value of: " << ReSTL::min_element<int>(array.begin(), array.end()) << "." <<endl;
	cout << "The vector<int> instance has a max element value of: " << ReSTL::max_element<int>(array.begin(), array.end()) << "." <<endl;
	cout << "The vector<int> instance has a total sum of: " << ReSTL::accumulate(array.begin(), array.end(), 0, [](int value){
		return value; }) << endl;
		auto res = ReSTL::find(array2.begin(), array2.end(), 3);
		if(res != array2.end()){
			cout << "The vector<int> instance contains the value: " << *res << endl;
		}

		auto array3 = ReSTL::Array<int>(5);
		ReSTL::copy_backwards(array.begin(), array.end(), array3.end());

		ReSTL::vector<int> vect1;
		vect1.push_back(1);
		vect1.push_back(2);
		vect1.push_back(3);
		vect1.push_back(4);
		vect1.push_back(5);

		cout << "Print vector<int> elements" << endl;
		ReSTL::foreach(vect1.begin(), vect1.end(), [](int value) { cout << value << endl; });

		return 0;
}

