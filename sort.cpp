#include <bits/stdc++.h>
using namespace std;

#define max(a,b) ((a)>(b)?(a):(b))

template<int ...vals>
struct Array;

template<int Head>
struct Array<Head> {
    constexpr static int val[] = {Head};
    constexpr static int head = Head;
    typedef Array<> next_arr;
};


template<int Head, int ...vals>
struct Array<Head, vals...> {
    constexpr static int val[] = {Head, vals...};
    constexpr static int head = Head;
    typedef Array<vals...> next_arr;
};

template<>
struct Array<> {
    constexpr static int val[] = {};
    constexpr static int head = -1;
    typedef Array<> next_arr;
};


template<int idx, typename A, typename B>
struct Split;

template<int ...A, int ...B>
struct Split<0, Array<A...>, Array<B...>> {
    typedef Array<A...> left;
    typedef typename Array<B...>::next_arr right;
};


template<int idx, int ...A, int ...B>
struct Split<idx, Array<A...>, Array<B...>> {
    typedef Split<idx - 1, Array<A..., Array<B...>::head>, typename Array<B...>::next_arr> cur;
    typedef typename cur::left left;
    typedef typename cur::right right;
};

template<typename A,typename B>
struct Merge;

template<int ...lhs, int ...rhs>
struct Merge<Array<lhs...>, Array<rhs...>> {
    typedef Array<lhs...,rhs...> res;
};

template<typename U, typename V>
struct FindMax;

template<int ...Looped, int ...unLooped>
struct FindMax<Array<Looped...>,Array<unLooped...>> {
    typedef FindMax<Array<Looped..., Array<unLooped...>::head>, typename Array<unLooped...>::next_arr> nxt;
    constexpr static int Max = max(nxt::Max, Array<unLooped...>::head);
    constexpr static int id = nxt::Max > Array<unLooped...>::head ? nxt::id : sizeof...(Looped);
};

template<int ...Looped>
struct FindMax<Array<Looped...>,Array<>> {
    constexpr static int Max = -1;
    constexpr static int id = sizeof...(Looped);
};

template<typename U, typename V>
struct Sort;

template<int ...Looped, int ...unLooped>
struct Sort<Array<Looped...>, Array<unLooped...>> {
    typedef FindMax<Array<>, Array<unLooped...>> MaxFound;
    constexpr static int Max = MaxFound::Max;
    constexpr static int id = MaxFound::id;
    typedef Split<id, Array<>, Array<unLooped...>> Sp;
    typedef Sort<Array<Looped..., Max>, typename Merge<typename Sp::left, typename Sp::right>::res> nxt_Loop;
    typedef typename nxt_Loop::sorted sorted;
};

template<int ...Looped>
struct Sort<Array<Looped...>, Array<>> {
    typedef Array<Looped...> sorted;
};

template<int ...data>
struct Sortwork {
    typedef Sort<Array<>,Array<data...>> sort_type;
    constexpr static int size = sizeof...(data);
    constexpr static auto x = sort_type::sorted::val;
};


#undef max


typedef Sortwork<1,4,2,1,78,2,4,54,11,4> result;

// https://www.cnblogs.com/ink19/p/cpp_template_select_sort.html

int main() {
    for(int i=0;i<10;++i)
        cout<<result::x[i]<<" ";
    cout<<endl;
}