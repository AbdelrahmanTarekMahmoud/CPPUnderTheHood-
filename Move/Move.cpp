#include <iostream>

template<typename T>
constexpr typename std::remove_reference<T>::type&& my_move(T&& arg) noexcept {
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
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
    Widget w2(std::move(w1)); //calls the move cotr
    Widget w3;
    w3 = std::move(w2);//calls the move assignment 

}    