#include <iostream>

/*
Forwarding Mainly rely on "reference collapsing".
So What is reference Collapsing ?!
 *set of rules in C++ that govern how references behave when you have multiple layers of references
the rule says : when there is a lvalue ref in the expression the reference will collapse to lvalue ref else it will collapse to rvalue ref

Example :
T& &    ===> T&   (LVALUE REF + LVALUE REF  =  LVALUE REF)
T& &&   ===> T&   (LVALUE REF + RVALUE REF  =  LVALUE REF)
T&& &   ===> T&   (RVALUE REF + LVALUE REF  =  LVALUE REF)
T&& &&  ===> T&&  (RVALUE REF + RVALUE REF  =  RVALUE REF)

-So in our forward template function lets try what happens when we push a lvalue ref and rvalue ref to it 

Case(1) ** Lvalue Ref ** (Widget&)

template<typename T>
constexpr Widget& && forward(remove_reference_t<Widget&> & param) noexcept
{
    return static_cast<Widget& &&>(param);
}

After the reference collapsing 

template<typename T>
constexpr Widget&  forward(Widget& param) noexcept
{
    return static_cast<Widget&>(param);  // here we ended with casting into Lvalue ref 
}

Case(2) ** Rvalue Ref ** (Widget&&)

template<typename T>
constexpr Widget&& && forward(remove_reference_t<Widget&&> & param) noexcept
{
    return static_cast<Widget&& &&>(param);
}

After the reference collapsing 
template<typename T>
constexpr Widget&&  forward(Widget & param) noexcept
{
    return static_cast<Widget&&> param); // here we ended with casting into Rvalue ref 
}

*/

// our forward function 
template<typename T>
constexpr T&& my_forward(std::remove_reference_t<T> & param) noexcept
{
    return static_cast<T&&>(param);
}

// From here all these lines of codes are for testing purpose only 
class Widget
{
public:
    Widget(){std::cout << "Widget Constructor !" << std::endl;}
    Widget(Widget&&){std::cout <<"Widget Move Constructor !"<< std::endl;}
    Widget&& operator = (Widget&&){std::cout <<"Widget Move Assignment operator !"<< std::endl;}
};

void func(const Widget &)
{
    std::cout << "lvalue version" << std::endl;
}
void func(Widget &&)
{
    std::cout << "rvalue version" << std::endl;
}

template<typename T>
void Process(T&& param)
{
    func(my_forward<T>(param));
}

int main()
{
   Widget W;
   Process(W); //calls the lvalue version 
   Process(std::move(W)); //calls the rvalue version

}    