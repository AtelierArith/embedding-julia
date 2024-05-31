// https://docs.julialang.org/en/v1/manual/embedding/

#include <julia.h>
JULIA_DEFINE_FAST_TLS // only define this once, in an executable (not in a shared library) if you want fast code.

int main(int argc, char *argv[])
{
    /* required: setup the Julia context */
    jl_init();

    /* run Julia commands */
    char* msg = "Hello, world!";
    jl_value_t *jl_input = (jl_value_t*)jl_cstr_to_string(msg);
    jl_function_t* println = jl_get_function(jl_base_module, "println");
    jl_call1(println, jl_input);

    /* strongly recommended: notify Julia that the
         program is about to terminate. this allows
         Julia time to cleanup pending write requests
         and run all finalizers
    */
    jl_atexit_hook(0);
    return 0;
}
