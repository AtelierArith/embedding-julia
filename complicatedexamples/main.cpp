#include <iostream>
#include <string>
#include <vector>

#include <julia.h>

JULIA_DEFINE_FAST_TLS // only define this once, in an executable (not in a shared library) if you want fast code.

/*
https://github.com/JuliaLang/julia/blob/d8f37c9920a079738dc01899deed7bd1a9f19d3a/src/julia.h#L1890
*/
int main(int argc, char *argv[])
{
    /* required: setup the Julia context */
    jl_init();

    /* run Julia commands */
    jl_eval_string("using Pkg; Pkg.activate(\".\")");
    jl_eval_string("using Pkg; Pkg.add(\"Example\")");
    jl_eval_string("using Example");

    jl_function_t* hello = jl_get_function(jl_main_module, "hello");
    std::string msg = "World";
    jl_value_t *jl_input = (jl_value_t*)jl_cstr_to_string(msg.c_str());
    jl_value_t *ret = jl_call1(hello, jl_input);
    if (jl_is_string(ret)){
        const char *c_str = jl_string_ptr(ret);
        std::string s(c_str);
        std::cout << s << std::endl;
    }
    else{
        printf("ERROR: unexpected return type\n");
    }

    ret = jl_eval_string("sqrt(2)");

    if (jl_typeis(ret, jl_float64_type)){
        double d = jl_unbox_float64(ret);
        std::cout << d << std::endl;
    }

    // call reverse function
    std::vector<double> v = {1,2,3,4,5};
    // The last argument `0` is a boolean indicating whether Julia should take ownership of the data. 
    // If this argument is non-zero, the GC will call free on the data pointer when the array is no longer referenced.
    jl_value_t* array_type = jl_apply_array_type((jl_value_t*)jl_float64_type, 1);
    jl_array_t *x = jl_ptr_to_array_1d(array_type, v.data(), v.size(), 0);
    jl_function_t *func = jl_get_function(jl_base_module, "reverse!");
    jl_call1(func, (jl_value_t*)x);
    double *xData = (double*)jl_array_data(x);

    std::vector<double> w(xData, xData + jl_array_len(x));
    for(double x : w) {
        std::cout << x << std::endl;
    }

    jl_eval_string("struct MyType{T}; p::T; q::T; end");

    jl_value_t *mt = jl_eval_string("MyType{Float64}(1.2, 2.4)");
    std::string field_name = "p";
    ret = jl_get_field(mt, field_name.c_str());
    if (jl_typeis(ret, jl_float64_type)){
        double d = jl_unbox_float64(ret);
        std::cout << d << std::endl;
    }
    field_name = "q";
    ret = jl_get_field(mt, field_name.c_str());
    if (jl_typeis(ret, jl_float64_type)){
        double d = jl_unbox_float64(ret);
        std::cout << d << std::endl;
    }

    jl_value_t *MyType = jl_eval_string("MyType");
    jl_value_t *p = jl_box_float64(1.2);
    jl_value_t *q = jl_box_float64(99.9);
    jl_value_t *MyTypeFloat64 = jl_apply_type1(MyType, (jl_value_t*)jl_float64_type);
    mt = jl_call2(MyTypeFloat64, p, q);
    ret = jl_get_field(mt, field_name.c_str());
    if (jl_typeis(ret, jl_float64_type)){
        double d = jl_unbox_float64(ret);
        std::cout << d << std::endl;
    }

    /* strongly recommended: notify Julia that the
         program is about to terminate. this allows
         Julia time to cleanup pending write requests
         and run all finalizers
    */
    jl_atexit_hook(0);
    return 0;
}
