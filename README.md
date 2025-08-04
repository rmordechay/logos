# Logos Programming Language

## Build

## Basic syntax
#### Hello world
```
main() {
    print("Hello world")
}
```

#### Variable Declaration
```
main() {
    x = 3
    y = 4
    z = x
    print(z)
}
```

#### Unary and Binary Operations
```
main() {
    a = (1 + 4) - (6 * 5) / 2
    b = a % 5
    d = 0
    d++
    d--
}
```

### Conditional
#### If statement
```
main() {
    x = 3
    y = 4
    if x > y {
        print("x is greater than y")
    } else x < y {
        print("x is less than y")
    } else {
        print("x is equal to y")
    }
}
```

#### Pattern Matching
```
enum Enum {
    ENUM1
    ENUM2
    ENUM3
}

main() {
    e = Enum.ENUM1
    if e {
        ENUM1: { print(ENUM1) }
        ENUM2: { print(ENUM2) }
        ENUM3: { print(ENUM3) }
    }
    
    str = "some string"
    if str {
        "some string": { print("some string") }
        "other string": { print("other string") }
        else: { print("default string") }
    }
}
```

### Iteration
#### Range Loop
To iterate over an index, use the range loop. The range loop has one variable loop, usually named 'i'. The range
'for i in n..m' which will iterate m - n times, from n to m - 1.
```
main() {
    x = 10
    for i in 5..x {
        print(i)
    }
}
```

prints:
```
5
6
7
8
9
```

```
main() {
    x = 10
    for i in ..x {
        print(i)
    }
}
```

#### Foreach Loop
```
main() {
    arr = [1, 2, 3]
    for element in arr {
        print(element)
    }
    for i, element in arr {
        print(i)
        print(element)
    }
    for i in arr.len() {
        print(arr[i])
    }
}
```

#### Infinite Loop
```
main() {
    for i {
        print(i)
        if i == 10 {
            break
        }
    }
    for {
        print("in infitine loop")
        if true {
            break
        } 
    }
}
```
