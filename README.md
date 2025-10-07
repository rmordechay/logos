# Logos Programming Language

## Build
### Requirements
- clang 19
- LLVM 19
- boost
- cmake

#### Linux

#### Mac

#### Windows
Not working yet.

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
    // Implicit typing
    x = 3
    y = 4
    z = x + y
    print(z)
    
    // Explicit typing
    x: Int = 3
    y: Long = 4
    z: Float = y / 3
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
#### If Statement
Logos doesn't have 'else if' but uses only 'else + condition'.
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
To iterate over an index, use the range loop. The range loop has one variable loop, usually named 'i'.
```
main() {
    x = 10
    for i in 5..x {
        print(i)
    }
}
```
Or
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
}
```

#### Infinite Loop
```
main() {
    for {
        print("in infitine loop")
        if true {
            break
        } 
    }
}
```

### Loop Meta Varaibles
#### 'for.i'

#### 'for.isFirst' and 'for.isLast'
You can hook into the first and last iteration of a loop using special constructs called 'for.isFirst' and 'for.isLast' instead
of calculating the index yourself.
```
main() {
    for i in 5..x {
        if for.isFirst {
            print(i)
        }
        if for.isLast {
            print(i)
        }
    }
}
```
Prints:
```
5
9
```

### Control Flow
```
func() {
    for i in 5..10 {
        if i > 2 {
            break
        }
        if i == 5 {
            continue
        }
        if i == 9 {
            return
        }
    }
}
main() {
    func()
}
```
You can also break from if statement using 'break if'. This will break from the outermost
if. For example:
```
main() {
    if true {
        if true {
            print("inside nested if")
            break if
        }
        print("inside if")
    }
}
```
Prints:
```
inside nested if
```
