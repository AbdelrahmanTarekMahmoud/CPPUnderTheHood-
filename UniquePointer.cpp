#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>

//Template class that takes (T -> for the resource Type) (Deleter -> for the custom Deleter)
template<typename T  , typename Deleter = std::default_delete<T>> //as default Deleter = std::default_delete<T>
//where std::default_delete<T> is
//template<typename T>
//struct std::default_delete {
//    void operator()(T* ptr) const {
//        delete ptr;
//    }
//};
class UniquePointer
{
private:
    T* _ptr{nullptr}; //resource to be managed (Raw Pointer) initialized with nullptr
    Deleter _deleter;   //custom Deleter
public:
    //explicit to avoid implicit conversions
    explicit UniquePointer(T* ptr , Deleter deleter = Deleter()) : _ptr(ptr) , _deleter(deleter){}
    //destructor calls the customdeleter on the our resource
    ~UniquePointer()
    {
        if(_ptr != nullptr)
        {
            _deleter(_ptr);
        }
    }
    //deleted CopyConstructor and Copy assignment (Move only Type)(Unique ownership)
    UniquePointer(const UniquePointer& other) = delete;
    UniquePointer& operator = (const UniquePointer& ohter) = delete;

    //Move Cotr && Move assignment operator (notice here we moved _deleter because it is move only type)
    UniquePointer(UniquePointer&& other) noexcept : _ptr(other._ptr) , _deleter(std::move(other._deleter))
    {
        other._ptr = nullptr;
    }
    UniquePointer& operator = (UniquePointer&& other) noexcept
    {
        if(this == &other) return *this;
        reset();
        _ptr = other._ptr;
        _deleter = std::move(other._deleter);
        other._ptr = nullptr;   
        return *this;
    }
    //Operators
    T& operator* () const
    {
        return *_ptr;
    }
    T* operator-> () const
    {
        return _ptr;
    }
    //return the rawPoitner(our resource) without changing ownership
    T* get() const
    {
        return _ptr;
    }
    //return the raw pointer and sets internal ptr to nullptr (transfer of ownership)
    T* release()
    {
        T* temp = _ptr;
        _ptr = nullptr;
        return temp;
    }
    //delete currently managed resource
    void reset(T* newPtr = nullptr)
    {
        if(_ptr != newPtr)
        {
            _deleter(_ptr);
            _ptr = newPtr;
        }
    }
    void swap(UniquePointer &other) noexcept
    {
        std::swap(_ptr , other._ptr);
        std::swap(_deleter , other._deleter);
    }
};
void testForGet(int *rawPtr)
{
    std::cout << "From test ForGet rawPtr is : " << *rawPtr << std::endl;
}
class Widget
{
public:
    explicit Widget() {std::cout << "Widget Constructor !" << std::endl;}
    ~Widget(){std::cout << "Widget Destructor !" << std::endl;}
};
int main()
{
    UniquePointer<Widget> Ptr1(new Widget());
    //UniquePointer<Widget> Ptr2(Ptr1); ERROR! Copy Cotr is deleted 
    //Ptr2 = Ptr1 ERROR! Copy assignment operator is deleted
    UniquePointer<int> Ptr2(new int(42));
    std::cout << *Ptr2 << std::endl; // Print : 42
    auto customDeleter{[](auto * ptr)
    {
        std::cout <<"CustomDeleter Fired" << std::endl;
        delete ptr;
    }
    };
    UniquePointer<int , decltype(customDeleter)> Ptr3(new int(2) , customDeleter); // Print : customDeleter Fired
    testForGet(Ptr2.get()); //print : From test ForGet rawPtr is : 42
}    