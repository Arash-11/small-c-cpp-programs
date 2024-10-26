```cpp
#include <iostream>
#include <utility>
#include <vector>

void move_add_three_and_print(std::vector<int> &&vec) {
  std::vector<int> vec1 = std::move(vec);
  vec1.push_back(3);
  for (const int &item : vec1) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

void add_three_and_print(std::vector<int> &&vec) {
  vec.push_back(3);
  for (const int &item : vec) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

void ptr_add_three_and_print(std::vector<int> *vec) {
  vec->push_back(3);
  for (const int &item : *vec) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

void ref_add_three_and_print(std::vector<int> &vec) {
  vec.push_back(3);
  for (const int &item : vec) {
    std::cout << item << " ";
  }
  std::cout << "\n";
}

void print_before() {
  std::cout << "before: ";
}

void print_after(std::vector<int> vec) {
  std::cout << "after: ";
  for (const int &item : vec) {
    std::cout << item << " ";
  }
  std::cout << "\n\n";
}

int main() {
  std::cout << "move_add_three_and_print" << "\n";
  print_before();
  std::vector<int> vec_1 = {1, 2};
  move_add_three_and_print(std::move(vec_1));
  print_after(vec_1);

  std::cout << "add_three_and_print" << "\n";
  print_before();
  std::vector<int> vec_2 = {1, 2};
  add_three_and_print(std::move(vec_2));
  print_after(vec_2);

  std::cout << "ptr_add_three_and_print" << "\n";
  print_before();
  std::vector<int> vec_3 = {1, 2};
  ptr_add_three_and_print(&vec_3);
  print_after(vec_3);

  std::cout << "ref_add_three_and_print" << "\n";
  print_before();
  std::vector<int> vec_4 = {1, 2};
  ref_add_three_and_print(vec_4);
  print_after(vec_4);

  return 0;
}

/*
g++ -std=c++11 -Wall -Werror -Wextra -o main main.cpp && ./main

move_add_three_and_print
before: 1 2 3 
after: 

add_three_and_print
before: 1 2 3 
after: 1 2 3 

ptr_add_three_and_print
before: 1 2 3 
after: 1 2 3 

ref_add_three_and_print
before: 1 2 3 
after: 1 2 3
*/
```

## Value semantics, move semantics, rvalue reference

Move semantics in C++ are a useful concept that allows for the efficient and optimized transfer of ownership of data between objects. One of the main goals of move semantics is to increase performance, since moving an object is faster and more efficient than deep copying the object.

<br />

More about the relationship between value and move semantics: https://laike9m.com/blog/revisiting-move-semanticsand-all-the-related-idioms,114/.

<br />

To understand move semantics, one must understand the concept of lvalues and rvalues. A simplified definition of lvalues is that lvalues are objects that refer to a location in memory. Rvalues are anything that is not a lvalue.

`std::move` is the most common way of **indicating to the compiler** the intention of moving an object from one lvalue to another. `std::move` casts an expression to a rvalue. This allows for us to interact with a lvalue as a rvalue, and allows for the ownership to be transferred from one lvalue to another.

More here: https://github.com/cmu-db/15445-bootcamp/blob/main/src/move_semantics.cpp.

And here: https://stackoverflow.com/questions/3413470/what-is-stdmove-and-when-should-it-be-used.

And here: https://youtu.be/sfbkMgwZITg.

<br />

`&&` is new in C++11. `int&& a` means "a" is an rvalue reference. `&&` is normally only used to declare a parameter of a function. And it *only* takes a r-value expression.

The simple explanation of an rvalue is that it doesn't have a memory address. E.g. the number 6, and character 'v' are both rvalues. `int a`, a is an lvalue, however `(a+2)` is an rvalue.

<br />

What’s the point of rvalue references?

Rvalue references add the possibility to express a new intention in code: **disposable objects**. When someone passes an rvalue over to you (as a reference), it means **they no longer care about it**.

```cpp
void SomeMethod(MyClass&& x) {
  // Caller doesn't care about x. do whatever you want with it.
}
```

<br />

Detailed blog post: https://blog.vero.site/post/rvalue-references.

<br />

Also note the following differences:

```diff
  #include <iostream>
  
  class String {
  public:
    String() = default;
  
    String(const char* string) {
      printf("created!\n");
      m_Size = strlen(string);
      m_Data = new char(m_Size);
      memcpy(m_Data, string, m_Size);
    }
  
    String(const String& other) {
      printf("copied!\n");
      m_Size = other.m_Size;
      m_Data = new char(m_Size);
      memcpy(m_Data, other.m_Data, m_Size);
    }
  
    String(String&& other) {
      printf("moved!\n");
      m_Size = other.m_Size;
      m_Data = other.m_Data;
  
      other.m_Size = 0;
      other.m_Data = nullptr;
    }
  
    ~String() {
      printf("destroyed!\n");
      delete m_Data;
    }
  
    void Print() {
      for (uint32_t i = 0; i < m_Size; i++)
        printf("%c", m_Data[i]);
  
      printf("\n");
    }
  
  private:
    char *m_Data;
    uint32_t m_Size;
  };
  
  class Entity {
  public:
    Entity(const String& name)
      : m_Name(name) {}
  
    Entity(String&& name)
-     : m_Name(name) {}
+     : m_Name((String&&)name) {} // same as `m_Name(std::move(name))`
  
    void PrintName() {
      m_Name.Print();
    }
  
  private:
    String m_Name;
  };
  
  int main() {
    Entity entity("goat");
    entity.PrintName();
  
    return 0;
  }

  /*
  g++ -std=c++11 -Wall -Werror -Wextra -o main main.cpp && ./main
  created!
- copied!
+ moved!
  destroyed!
  GOAT
  destroyed!
  */
```
