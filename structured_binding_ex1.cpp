/*
@file structured_binding_ex1.cpp

@brief Example demonstrating structured binding of auto-variables to items of pair/tuple return values.
*/

#include <iostream>
#include <utility>  // std::pair<T1, T2>
#include <tuple>
#include <string>


auto pair_retval(int a, std::string s)
{
    auto p = std::make_pair(a, s);
    
    return(p);
}



auto tuple_retval(int a, float b, std::string s)
{
    auto p = std::make_tuple(a, b, s);
    
    return(p);
}


auto composite_retval(int a, int b, std::string c, std::string s)
{
    auto p1 = pair_retval(a, c);
    auto p2 = pair_retval(b, s);
    
    auto p_comp = std::make_pair(p1, p2);
    
    return(p_comp);
}


using err_chk_t = std::pair<bool, int>;

auto some_err_func(int inp)
{
    int err_code = 0;
    float outp = 0.0F;
    bool failed = false;
    
    if (10 < inp)
    {
        err_code = 1;
        failed = true;
    }
    else if (-10 > inp)
    {
        err_code = -1;
        failed = true;
    }
    else
    {
        outp = inp * 1.25F;
        failed = false;
    }
    
    auto chk = std::make_pair(failed, err_code);
    auto ret = std::make_pair(chk, outp);
    
    return(ret);
}


void check_retval(err_chk_t chk, auto val)
{
    auto [failed, code] = chk;
    
    std::cout << failed << " " << code << " " << val << std::endl;
    
    if (failed)
    {
        std::cout << "ERROR: cannot show value! Code = " << code << std::endl;
    }
    else
    {
        std::cout << "SUCCESS: value = " << val << std::endl;
    }
}


// *********************************** TESTING ******************************************

int main()
{
    auto [a, b] = pair_retval(123, "357-ABC");
    std::cout << a << b << std::endl;
    
    auto [c, d, e] = tuple_retval(789, -5.28F, "123-DEF");
    std::cout << c << d << e << std::endl;
    
    auto [p1, p2] = composite_retval(789, 123, "123", "DEF");
    // NOTE: need to do awkward 2-step (un-)binding then binding!!
    auto [r1, r2] = p1;
    auto [r3, r4] = p2;
    std::cout << r1 << r2 << r3 << r4 << std::endl;
    
    auto [f, g] = some_err_func(5);
    check_retval(f, g);
    
    auto [i, j] = some_err_func(-11);
    check_retval(i, j);
    
    auto [m, n] = some_err_func(11);
    check_retval(m, n);
    
    
    return 0;
}


