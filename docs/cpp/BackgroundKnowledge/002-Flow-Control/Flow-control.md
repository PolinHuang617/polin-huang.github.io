## `condition ? expr1 : expr2`

```cpp
condition
    ? expr1
    : expr2;
```

## `if-else`
```cpp
if (condition0) {
    // code ...
}
else if (condition1){
    // code ...
}
else {
    // code ...
}
```

## `switch`
```cpp
switch(enum_condition) {
    case enum0: {
        // code ...
        break;
    }
    case enum1:
    case enum2:
    case enum3: {
        // code ...
        break;
    }
    default:
        // code ...
        break;
}
```

## `while`
```cpp
while(condition) {
    // code ...
}

do {

} while(condition);
```

## `for`
```cpp
// Basic for loop
for (std::size_t i = 0; i < vec.size(); ++i) {
    // code ...
}

// iter can be changeable loop
for (auto iter  = vec.begin(); iter != vec.end(); ++iter) {
    // code ...
}

// iter is const
for (auto iter = vec.cbegin(); iter != vec.cend(); ++iter) {
    // code ...
}

// range for loop, changeable
for (auto &iter : vec) {
    iter = ...;
}

// ange for loop, unchangeable
for (const auto &iter : vec) {
    // readonly operation ...
}
```
