# CPPUnderTheHood
A comprehensive deep dive into the core mechanisms of C++, this repository provides clear and straightforward implementations of fundamental C++ features, helping users understand how these concepts work under the hood
## Repository Contents
1. [std::unique_ptr](https://github.com/AbdelrahmanTarekMahmoud/CPPUnderTheHood/blob/main/UniquePointer/UniquePointer.cpp)
2. [std::move](https://github.com/AbdelrahmanTarekMahmoud/CPPUnderTheHood/blob/main/Move/Move.cpp)
    #### Move Notes:
             * Using of T&& arg : T&& is a universal reference so it binds to Lvalues and Rvalues
             * Using of constxpr : to evaluate at compile-time
             * Using std::remove_reference_t<T> : to remove any references of (arg)
             * Using noexcept : to tell the compiler that function doesnt throw exceptions(optimize)
3. [std::forward](https://github.com/AbdelrahmanTarekMahmoud/CPPUnderTheHood/blob/main/Forward/forward.cpp)

  

     

