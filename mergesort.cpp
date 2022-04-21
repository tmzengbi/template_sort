#include <bits/stdc++.h>
using namespace std;

template<typename A, typename B, bool condition>
struct check_if;

template<typename A, typename B>
struct check_if<A, B, true> {
    typedef A value;
};

template<typename A, typename B>
struct check_if<A, B, false> {
    typedef B value;
};

template<int ...Vals>
struct Array;

template<>
struct Array<>{
    constexpr static int head = -1;
};

template<int Head, int ...Vals>
struct Array<Head, Vals...> {
    constexpr static int a[] = {Head, Vals...};
    constexpr static int head = Head;
    typedef Array<Vals...> next;
};

using emptyArray = Array<>;

template<int index, typename A, typename B>
struct Split;

template<int ...front, int ...back>
struct Split<0, Array<front...>, Array<back...>> {
    typedef Array<front...> left;
    typedef Array<back...> right;
};
template<int index, int ...front, int ...back>
struct Split<index, Array<front...>, Array<back...>> {
    typedef Split<index - 1, Array<front..., Array<back...>::head>, typename Array<back...>::next> splitArray;
    typedef typename splitArray::left left;
    typedef typename splitArray::right right;
};

template<typename sorted, typename A, typename B>
struct Merge;

template<int ... sorted>
struct Merge<Array<sorted...>, emptyArray, emptyArray> {
    typedef Array<sorted...> sortedArray; 
};

template<int ... sorted, int ...front>
struct Merge<Array<sorted...>, Array<front...>, emptyArray> {
    typedef typename Merge<Array<sorted..., Array<front...>::head>, typename Array<front...>::next, emptyArray>::sortedArray sortedArray;
};

template<int ... sorted, int ...back>
struct Merge<Array<sorted...>, emptyArray, Array<back...>> {
    typedef typename Merge<Array<sorted..., Array<back...>::head>, emptyArray, typename Array<back...>::next>::sortedArray sortedArray;
};

template<int ... sorted, int ...front, int ...back>
struct Merge<Array<sorted...>, Array<front...>, Array<back...>> {
    typedef typename check_if<Merge<Array<sorted..., Array<back...>::head>, Array<front...>, typename Array<back...>::next>,
                        Merge<Array<sorted..., Array<front...>::head>, typename Array<front...>::next, Array<back...>>,
                        (Array<front...>::head > Array<back...>::head)>::value::sortedArray sortedArray;
};

template<typename A>
struct MergeSort;

template<>
struct MergeSort<emptyArray> {
    typedef emptyArray sortedArray;
};

template<int Val>
struct MergeSort<Array<Val>> {
    typedef Array<Val> sortedArray;
};

template<int ...Vals>
struct MergeSort<Array<Vals...>> {
    constexpr static int len = sizeof...(Vals);
    constexpr static int half = len / 2;
    typedef typename Split<half, emptyArray, Array<Vals...>>::left left;
    typedef typename Split<half, emptyArray, Array<Vals...>>::right right;
    typedef typename MergeSort<left>::sortedArray sortedLeft;
    typedef typename MergeSort<right>::sortedArray sortedRight;
    typedef typename Merge<emptyArray, sortedLeft, sortedRight>::sortedArray sortedArray;
};


typedef Array<15,1,3,6,1,23,54> arr;
int main() {
    for(int i = 0; i < 7; ++ i)
        cout<<MergeSort<arr>::sortedArray::a[i]<<endl;
}