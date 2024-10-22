#include <iostream>

template<typename T>
constexpr  std::remove_reference<T>&& my_move(T&& arg) noexcept {
    return static_cast<std::remove_reference<T>&&>(arg);
}

class Widget
{
public:
    Widget(){std::cout << "Widget Constructor !" << std::endl;}
    Widget(Widget&&){std::cout <<"Widget Move Constructor !"<< std::endl;}
    Widget&& operator = (Widget&&){std::cout <<"Widget Move Assignment operator !"<< std::endl;}
};
int main()
{
    Widget w1;
    Widget w2(my_move(w1)); //calls the move cotr
    Widget w3;
    w3 = my_move(w2);//calls the move assignment 

}    
