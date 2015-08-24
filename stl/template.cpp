template <class a_type> class a_class {...};//a class with template of data-type a_type
a_type a_var; //a_var is a variable of datatype a_type
template<class a_type> void a_class<a_type>::a_function(){...}//define a function as a member of a templated class
a_class<int> an_example_class;//declaring an instance of a class
