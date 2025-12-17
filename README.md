# Logos Programming Language

## Build
### Requirements
- C++ compiler
- LLVM 19
- cmake

#### Linux

#### Mac

#### Windows
Not working yet.

## Overview
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

#### Statements Block
Statements Block is a collection of statements wrapped in curly braces and can be part of a function,
for loop, if statement, etc. If only one statement exists in the block, you can omit the braces altogether (similar to C/C++).
```
// Block with multiple statements and braces - valid
main() {
    x = 3
    y = 4
}

// Block with one statement without braces - valid
main() print("Hello world")

// Block with multiple statements without braces - invalid!
main() 
    x = 3
    y = 4
```

#### If Statement
```
main() {
    x = 3
    y = 4
    if x > y {
        print("x is greater than y")
    } else if x < y {
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
    switch e {
        ENUM1: { print(ENUM1) }
        ENUM2: { print(ENUM2) }
        ENUM3: { print(ENUM3) }
    }
    
    str = "some string"
    switch str {
        "some string": print("some string")
        "other string": { print("other string") }
        else: { 
            print("default string") 
        }
    }
}
```

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
Or even (more on _for.i_ below).
```
main() {
    for 10 {
        print(for.i)
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
}
```

#### Infinite Loop
```
main() {
    for.ever {
        print("In infitine loop")
        if true break
    }
}
```

### Meta Variables
In Logos, there are special variables called Meta Variables that are namespaced with a keyword, for example, 'for.i'. These variables
will be automatically created and assigned a value once you will declare them. 

#### for.i
In for loops, you don't have to necessarily define an _i_ variable for iteration. Logos will generate it for you 
using the meta variable 'for.i'. For example
```
main() {
    for 10 {
        print(for.i)
    }
}
```
Prints:
```
0
1
...
8
9
```
#### for.isFirst and for.isLast
Likewise, you can hook into the first and last iteration of a loop using the _for.isFirst_ and _for.isLast_ variable instead
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

#### If Statement
If statements are done using the 'if', 'if else' and 'else' keyword, similar to other languages like Java, Go or C/C++. 
In Logos you don't have to wrap the condition in parenthesis. 
```
func() {
    a = 3
    if a > 2 {
        return
    }
    if a == 5 {
        return
    }
    if a <= 9 {
        return
    }
}

main() {
    func()
}
```

Sometimes you want to break from nested if statements. In Logos you can do this using 'break if' which will 
break from the outermost if. For example:
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

#### If Macro
tbd

### The _defer_ keyword
Similar to other languages, you can delay the execution of a function using the 'defer' keyword. For example
```
func(str: Str) {
    print(str)
}

main() {
    defer func("After")
    func("Before")
}
```
Prints:
```
Before
After
```

### The _io_ keyword
The second mechanism to handle IO connections is with the _io_ keyword. With this mechanism you
pass a pair of function names, like so: 
```
io(openFile, closeFile)
```
where the left function will be the opening
function and the right function will be the closing function. Now, once the io is declared, you can call 
the opening function (left-hand) with the io keyword, for example
```
io f = openFile() {
    // Do something
    // text = f.read()
} 
```
And you are done. You don't need to call closeFile. Logos will do it for you. Everytime you call the opening function
with the io keyword, the closing function will be called at the end of the scope, making sure your
resources are being freed correctly. 
