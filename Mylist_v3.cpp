#include<iostream>
using namespace std;

template<class T> class MyList;
template<class T> MyList<T> operator+(const MyList<T> &l1, const MyList<T> &l2);
template<class T> ostream &operator<<(ostream&os, const MyList<T>&obj);
template<class T> MyList<T> operator+(const MyList<T> &l1, const T &item);

class indexOutOfRange{};
class listIsEmpty{};
class ilegalIndex{};

template<class T>
class MyList{
	friend ostream & operator<< <T>(ostream &os, const MyList<T> &obj);//<< operator overloading 
	friend MyList<T> operator+ (const MyList<T> &l1, const MyList<T> &l2){
		MyList<T> tmp;
		while(tmp.size < l1.size + l2.size){
			tmp.double_space();
		}
		tmp.lastelem = l1.lastelem + l2.lastelem + 1;
		for(int i = 0; i <= l1.lastelem; ++i){
			tmp.a[i] = l1.a[i];
		}
		for(int i = l1.lastelem + 1; i <= tmp.lastelem; ++i){
			tmp.a[i] = l2.a[i - l1.lastelem - 1];
		}
		return tmp;
	}//+ operator overloading
	friend MyList<T> operator+(const MyList<T> &l1, const T &item){
		MyList<T> l2;
		l2 = l1;
		l2.push(item);
		return l2;
	}//+ operator overloading, return a new list without revising the fomer
	private:
		T *a;
		int size;
		int lastelem;
		void double_space(){
			T *b;
			size *= 2;
			b = new T[size];
			for(int i = 0;i <= lastelem; ++i){
				b[i] = a[i];
			}
			delete []a;
			a = b;
		}//double space of the list when there is no enough room for operating
	public: 
		MyList(int l = 100){
			size = l;
			lastelem = -1;
			a = new T[size];
		}//construct a list whose length is l, when there is no actual parameters, let the length be 100; 
		MyList(int num, const T&item){
			size = num;
			a = new T[size];
			for(int i = 0;i < num; ++i){
				a[i] = item;
			}
			lastelem = num - 1;
		}//add item to the list for num times
		MyList(const MyList<T> &l){
			size = l.size;
			lastelem = l.lastelem;
			delete []a;
			a = new T[size];
			for(int i = 0; i <= lastelem; ++i){
				a[i] = l.a[i];
			}
		}//copy a list
		MyList(T *arr, int len){
			size = len;
			a = new T[size];
			for(int i = 0;i < len; ++i){
				a[i] = arr[i];
			}
			lastelem = size - 1;
		}//construct a list with the fomer len elements of arr 
	    void push(const T &item);//add item to the last of list
        T pop() throw(listIsEmpty);//delete the last element in list, and return the element deleted 
		void insert(int index, const T&item) throw(indexOutOfRange);//insert item into list with the index place
		void clean();//clean list
		int get_size();//return the number of all elements in list
		void erase(int start, int end) throw(indexOutOfRange, ilegalIndex); //delete elements in list from start to end, start and end are included
		T get_item(int index) throw(indexOutOfRange);//return the element with index index
		MyList<T> get_item(int start, int end) throw(indexOutOfRange, ilegalIndex);//return elements in list from start to end, start and end are included, minus number is acceptable
		void remove(const T &item);//delete the first element in list which is equal to item
		void quicksort(T a[], int low, int high);
		int divide(T a[], int low, int high);
		void sort(bool less = true);//quick sort, if less = true, sort it from small to large, else, sort it from large to small 
		void reverse();//reverse all the element in list
		MyList<T> & operator=(const MyList<T> &l);//= operator overloading
		T &operator[](int index) throw(indexOutOfRange);//return the element in list with index index
		MyList<T> &operator +=(const T &item);//add item to the last of list
		int count(const T &item);//return the number of elements in list which are equal to item
		MyList<T> &operator+=(const MyList<T>&l1);//add a MyList to another one
		~MyList(){
			delete []a;
		}
};

//add a MyList to another one
template<class T>
MyList<T>& MyList<T>::operator+=(const MyList<T>&l1){
	*this = *this + l1;
	return(*this);
}

//return the number of elements in list which are equal to item
template<class T>
int MyList<T>::count(const T &item){
	int num = 0;
	for(int i = 0; i <= lastelem; ++i){
		if(a[i] == item){
			++num;
		}
	}
	return num;
}

//add item to the last of list
template<class T>
MyList<T>& MyList<T>::operator+=(const T &item){
	push(item);
	return *this;
}

//return the element in list with index index
template<class T>
T& MyList<T>::operator[](int index) throw(indexOutOfRange){
	if(index < 0 || index > lastelem)    throw(indexOutOfRange());
	return a[index];
} 

//delete the first element in list which is equal to item
template <class T>
void MyList<T>::remove(const T &item){
	for(int i = 0; i <= lastelem; ++i){
		if(a[i] == item){
			erase(i,i);return;
		}
	}
}

//reverse all the element in list
template<class T>
void MyList<T>::reverse(){
	MyList<T> tmp;
	tmp = *this;
	for(int i = 0; i <= lastelem; ++i){
		a[i] = tmp.a[lastelem - i]; 
	}
}

//quick sort, if less = true, sort it from small to large, else, sort it from large to small 
template<class T>
void MyList<T>::sort(bool less){
	int low;
	int high;
	low = 0;
	high = lastelem;
	quicksort(a, low, high);
	if(!less){
		reverse();
	}
}
template<class T>
void MyList<T>::quicksort(T a[], int low, int high){
	T mid;
	if(low >= high)    return ;
	mid = divide(a, low, high);
	quicksort(a, low, mid - 1);
	quicksort(a, mid + 1, high);
}

template<class T>
int MyList<T>::divide(T a[], int low, int high){
	T k = a[low];
	do{
		while(low < high && a[high] >= k)    --high;
		if(low < high){a[low] = a[high]; ++low;}
		while(low < high && a[low] <= k)    ++low;
		if(low < high){a[high] = a[low]; --high;}    
	}while(low!=high);
	a[low] = k;
	return low;
} 

//<< operator overloading
template<class T>
ostream &operator<<(ostream &os, const MyList<T> &obj){
	os << '[';
	for(int i = 0; i < obj.lastelem; ++i){
		os << obj.a[i] << ", ";
	} 
	if(obj.lastelem < 0){
		os << ']';
	}
	else os << obj.a[obj.lastelem] << ']';
	return os;
}
 
//add item to the last of list
template<class T>
void MyList<T>::push(const T &item){
	if(lastelem == size - 1){
    	double_space();
	}
	a[++lastelem] = item; 
} 

//delete the last element in list, and return the element deleted
template<class T>
T MyList<T>::pop() throw(listIsEmpty){
	if(lastelem < 0)    throw(listIsEmpty());
	return a[lastelem--];
}

//insert item into list with the index place
template<class T>
void MyList<T>::insert(int index, const T&item) throw(indexOutOfRange){
	if(index < 0 || index > lastelem + 1)    throw(indexOutOfRange());
	if(lastelem == size - 1){
		double_space();
	}
	for(int i = lastelem; i >= index; --i){
		a[i + 1] = a[i];
	}
	a[index] = item;
	++lastelem;
}

//clean list
template<class T>
void MyList<T>::clean(){
	size = 0;
	lastelem = -1;
}

//return the number of all elements in list
template<class T>
int MyList<T>:: get_size(){
	return (lastelem + 1);
}

//delete elements in list from start to end, start and end are included
template<class T>
void MyList<T>::erase(int start, int end) throw(indexOutOfRange, ilegalIndex){
	if(start > end)    throw(ilegalIndex());
	if(start < 0 || start > lastelem)    throw(indexOutOfRange());
	if(end < 0 || end > lastelem)    throw(indexOutOfRange());
	for(int i = start; i < start + lastelem - end; ++i){
		a[i] = a[i + end - start + 1];
	}
	lastelem = start + lastelem - end - 1;
}

//return the element with index index
template<class T>
T MyList<T>::get_item(int index) throw(indexOutOfRange){
	if(index < 0 || index > lastelem)    throw(indexOutOfRange());
	return a[index];
}

//return elements in list from start to end, start and end are included, minus number is acceptable
template<class T>
MyList<T> MyList<T>::get_item(int start, int end) throw(indexOutOfRange, ilegalIndex){
	if(start > end)    throw(ilegalIndex());
	if(start < 0 || start > lastelem)    throw(indexOutOfRange());
	if(end < 0 || end > lastelem)    throw(indexOutOfRange());
	if(start < 0)    start += (lastelem + 1);
	if(end < 0)    end += (lastelem + 1);
	if(start > end){
	    MyList<T> sub;
	   	return sub;
	}
	else{
		MyList<T> sublist(end - start + 1);
		for(int i = 0; i < end - start + 1; ++i){
			sublist.a[i] = a[start + i];
			++sublist.lastelem;
		}
		return sublist;
	}
}

//= operator overloading
template<class T>
MyList<T>& MyList<T>::operator=(const MyList<T> &l){
	if(this == &l){
		return *this;//avoid copying itself
	}
	delete []a;
	size = l.size;
	lastelem = l.lastelem;
	a = new T[size];
	for(int i = 0; i <= lastelem; ++i){
		a[i] = l.a[i];
	} 
	return *this;
} 

/*int main()
{   
    /*int arr[5];
    int poped1;
    for(int i = 0; i < 5; ++i){
    	arr[i] = i + 1;
	}
	MyList<int>c(arr, 5);
    cout << c << endl;
    MyList<int>sub;
    c.reverse();
    sub = c.get_item(2,3);
    sub = c + c;
    cout << sub << endl;
    cout << c << endl;
    c.remove(3);
    cout << c << endl << c[1] << endl;
    c+=1;
    cout << c << endl;
    c.sort();
    cout << c << endl;
    int co;
    co = c.count(1);
    cout << co << endl;
    cout << c + 1 << endl;
    cout << c << endl;
    c+=c;
	return 0;
*/
    /*MyList<int> a, b;
    int i;
    for(i = 0; i < 5; ++i){
    	a.push(i);
	}
	cout << a << endl;// a = [0, 1, 2, 3, 4]
	a[3] = 15;
	cout << a << endl;// a = [0, 1, 2, 15, 4]
	a.sort();
	cout << a << endl;// a = [0, 1, 2, 4, 15]
	a.reverse();
	cout << a << endl;// a = [15, 4, 2, 1, 0]
	//a.insert(0,1);
	//cout << a << endl;
	//a.insert(6,1);
	//cout << a << endl;
	//cout << a.get_item(10);
	//a.erase(-1,10);
	//cout << a << endl;
	//a. insert(8,1);
	//cout << a[5] << endl;
	a += 12;
	cout << a << endl;// a = [15, 4, 2, 1, 0, 12]
	for(i = 0; i < a.get_size(); ++i){
		cout << a.get_item(i) << endl;
	}
	cout << a.count(5) << endl;
	b.clean();
	cout << b << endl;
	cout << b.get_size() << endl;
	a.erase(2,5);
	cout << a << endl;//a = [15, 4]
	b = a + a;
	cout << b << endl;
	b.insert(3, 116);
	cout << b << endl;
	b.remove(4);
	cout << b << endl;
	MyList<double>c(10,3.14);
	cout << c << endl;
	for(i = 0; i < 100; ++i){
		c.push(1.1*i);
	}
	cout << c.get_item(100, 105) << endl;
	try{
		cout << a[100] << endl;
	}
	catch(indexOutOfRange){
		cout << "hahahaha";
	}
	return 0;
}*/
