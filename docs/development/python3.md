
## Syntax

### Variable assignment


```python
# Single variable assignment
index = 0

# Multiple variables assignment
a, b, c = 1, True, "HaHa"

```

- I don't need to declare `index` before I assigning to it.

- I don't need to tell Python what type is the variable.

>

Use `type()` to determine variable type

```python
type(index) # int

```

Python3 has 6 basic variable types

- Bool: `True` and `False`

- Number: 3 detailed types

```python
# int
var1, var2, var3, var4 = 1, -1, 0o22, 0x22
var5, var6 = 51924361L, -4721885298529L

# float
var7, var8, var9 = -21.9, 70.2e-12

# complex
var10 = -5e+3j

```

- String: Consists of numbers, letters, underlines

```python
s = 'abcdef'
s[0 : -1]  # s[begin, end], 'abcde', regardless of the last element
s[1 : -1 : 2]  #  s[begin, end, step], 'bd'

```

- List

```python
list = [ 'runoob', 786 , 2.23, 'john', 70.2 ]

```

- Tuple

```python
# Cannot be reassigned value
tuple = ( 'runoob', 786 , 2.23, 'john', 70.2 )

```

- Dictionary

```python
dict = {'name': 'runoob','code':6734, 'dept': 'sales'}

```



## Functions


```python
def least_difference(a, b, c = 3):
    """Return the smallest difference between any two numbers
    among a, b and c.
    
    >>> least_difference(1, 5, -5)
    4
    """
    diff1 = abs(a - b)
    diff2 = abs(b - c)
    diff3 = abs(a - c)
    return min(diff1, diff2, diff3)

```

## Condition


```python
def inspect(x):
    if x == 0:
        print(x, "is zero")
    elif x > 0:
        print(x, "is positive")
    elif x < 0:
        print(x, "is negative")
    else:
        print(x, "is unlike anything I've ever seen...")

inspect(0)
inspect(-15)

```


