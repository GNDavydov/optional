# Optional

## Implementation of the optional class

The class template std::optional manages an optional contained value, i.e. a value that may or may not be present.

A common use case for optional is the return value of a function that may fail. As opposed to other approaches, such as
std::pair<T,bool>, optional handles expensive-to-construct objects well and is more readable, as the intent is expressed
explicitly.

Any instance of optional<T> at any given point in time either contains a value or does not contain a value.

If an optional<T> contains a value, the value is guaranteed to be allocated as part of the optional object footprint,
i.e. no dynamic memory allocation ever takes place. Thus, an optional object models an object, not a pointer, even
though operator*() and operator->() are defined.

When an object of type optional<T> is contextually converted to bool, the conversion returns true if the object contains
a value and false if it does not contain a value.

## LINKS

https://en.cppreference.com/w/cpp/utility/optional

https://en.cppreference.com/w/cpp/types/aligned_storage

https://www.cppstories.com/2018/05/using-optional/

https://habr.com/ru/post/372103/
