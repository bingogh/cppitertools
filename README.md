cppitertools
============

range-based for loop add-ons inspired by the python builtins and itertools
library.


range
-----

Uses an underlying iterator to acheive the same effect of the python range
function.  `range` can be used in three different ways:

Only the stopping point is provided.  Prints 1 2 3 4 5 6 7 8 9
```c++
for (auto i : range(10)) {
    cout << i << '\n';
}
```

The start and stop are both provided.  Prints 10 11 12 13 14
```c++
for (auto i : range(10, 15)) {
    cout << i << '\n';
}
```

The start, stop, and step are all provided.  Prints 20 22 24 26 28
```c++
for (auto i : range(20, 30, 2)) {
    cout << i << '\n';
}
```

Negative values are allowed as well.  Prints 2 1 0 -1 -2
```c++
for (auto i : range(2, -3, -1)) {
    cout << i << '\n';
}
```


enumerate
---------

Can be used with any class with an iterator.  Continually "yields" containers
similar to pairs.  They are basic structs with a .index and a .element.  Usage
appears as:

```c++
vector<int> vec{2, 4, 6, 8};
for (auto e : enumerate(vec)) { 
    cout << e.index
         << ": "
         << e.element
         << '\n';
}
```


cycle
-----

Repeatedly produce all values of an iterable.  The loop will be infinite, so a
`break` is necessary to exit.

Prints 1 2 3 repeatedly until `some_condition` is true
```c++
vector<int> vec{1, 2, 3};
for (auto i : cycle(vec)) {
    cout << i << '\n';
    if (some_condition) {
        break;
    }
}
```