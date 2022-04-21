#include <bits/stdc++.h>
using namespace std;

template<int index, int val>
struct Element {
    constexpr static int id = index;
    constexpr static int value = val;
};
template<int index, int ...vals>
struct Array;

template<int index>
struct Array<index> {

};

template<int index, int head, int ...vals>
struct Array<index, head, vals...> {
    typedef Element<index, head> cur;
    typedef Array<index + 1, vals...> next;
};

template<typename Arr>
struct getMax;

template<int any>
struct getMax<Array<any>> {
    constexpr static int id = -1;
    constexpr static int value = -1;
};

#define max(a,b) ((a)>(b)?(a):(b))
template<int index, int ...val>
struct getMax<Array<index, val...>> {
    typedef Array<index, val...> arr;
    constexpr static int id = (arr::cur::value) > (getMax<typename arr::next>::value)
                                ?(arr::cur::id): (getMax<typename arr::next>::id);
    constexpr static int value = max(arr::cur::value, getMax<typename arr::next>::value);
};
#undef max

template<int index, typename A, typename B>
struct Split;

template<int ...front, int ...back>
struct Split<0, Array<front...>, Array<back...>> {
    typedef Array<front...> left;
    typedef typename Array<back...>::next right;
};

template<int index, int ...front, int ...back>
struct Split<index, Array<front...>, Array<back...>> {
    typedef Split<index - 1, Array<front..., Array<back...>::cur::value>, typename Array<back...>::next> cur;
    typedef typename cur::left left;
    typedef typename cur::right right;
};


template<typename A, typename B>
struct Merge;

template<int indexFront, int ...front, int indexBack, int ...back>
struct Merge<Array<indexFront, front...>, Array<indexBack, back...>> {
    typedef Array<0, front..., back...> merged;
};

template<typename Arr>
struct mysort;

template<typename Arr>
struct mysort {
    typedef getMax<Arr> maxElement;
    constexpr static int head = maxElement::value;
    typedef Split<maxElement::id, Array<0>, Arr> SplitArr;
    typedef typename Merge<typename SplitArr::left, typename SplitArr::right>::merged MergedArr;
    typedef mysort<MergedArr> next;
};

template<int any>
struct mysort<Array<any>> {

};
template<int ...vals>
using arr = Array<0, vals...>;
int main() {
    typedef arr<10,11,12,13,18,11> test;
    // cout<<getMax<test>::id<<" "<<getMax<test>::value<<endl;    
    cout<<mysort<test>::head<<endl;
    cout<<mysort<test>::next::head<<endl;
    cout<<mysort<test>::next::next::head<<endl;
    cout<<mysort<test>::next::next::next::head<<endl;
    cout<<mysort<test>::next::next::next::next::head<<endl;
    cout<<mysort<test>::next::next::next::next::next::head<<endl;
    // cout<<mysort<test>::next::next::next::next::next::next::head<<endl;
}


