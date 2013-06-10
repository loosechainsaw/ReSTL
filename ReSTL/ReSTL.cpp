
#include "stdafx.h"
#include <iostream>

namespace ReSTL{


	template<class T>
	class base_container{
	public:
		virtual T& operator[](int index) = 0;
		virtual T const & operator[](int index) const = 0;
		virtual int const size() const = 0;
		virtual ~base_container(){};
	};

	template<typename T>
	class Array : public ReSTL::base_container<T>{
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

		int const size() const override {
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

		T const & operator[](int index) const override{
			return elements[index];
		}

		T& operator[](int index) override{
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
		T* elements;
		int size_;
		int capacity_;
	};

	template<typename TIterator, typename TValueType>
	void fill(TIterator start, TIterator end, TValueType const & value){
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

	template<typename TIterator, typename TValueType>
	bool all_off(TIterator start, TIterator end, TValueType const & value){
		for(;start != end; ++start){
			if(*start != value) return false;
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

	template<typename TIterator, typename TValueType, typename TFunctor>
	TValueType accumulate(TIterator start, TIterator end, TValueType const & default_value, TFunctor functor){
		TValueType acc = default_value;
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

	template<typename TIterator, typename TValueType>
	TIterator find(TIterator start, TIterator end, TValueType const & value){
		for(;start != end; ++start){
			if(*start == value) return start;
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

template<class T>
void print_all(ReSTL::base_container<T>& container){
	using namespace std;
	for(int i = 0; i < container.size(); i++){
		cout << "Index: " << i << " , value: " << container[i] << endl;
	}
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
		return value; });
	auto res = ReSTL::find(array2.begin(), array2.end(), 3);
		if(res != array2.end()){
			cout << "The vector<int> instance contains the value: " << *res << endl;
		}


	cout << "Template arguement deduction" << endl;

	print_all(array2);

	return 0;
}

