# Задача 1: my_strlen

`// my_strlen()`

`int my_strlen(const char* str) {`
    `int i = 0;`
    `while(str[i]) {`
        `++i;`
    `}`
    `return i;` 
`}`

# Задача 2: на переполнение типов данных

`#include <iostream>`

`int main()`
`{`
    `unsigned char n = 256;`
    `for (unsigned char i = 0; i < n; ++i) // тк здесь мы подставим заместо n значение 256 то у нас будет переполнение типа тк unsigned char существует от 0 до 255. Как следствие 256 это 0, 257 это 1 и тд. По итогу цикл просто не выполнится`
    `{`
        `std::cout << "a"; // 256 "a"`
    `}`
    `unsigned char h = 128;`
    `for (unsigned char i = 0; i < 2 * h; ++i) расширение типов!`
    `{`
        `std::cout << "b"; // ну а здесь у нас ситуация такая же, только у нас здесь for будет работать до бесконечности.`
    `}`
`}`

Потому что `unsigned char` вмещает значения от 0 до 255, а 2 * h даёт 256, но из-за арифметического расширения до `int` сравнение i < 256 происходит в типе `int`, где i никогда не переполняется — оно переполняется только внутри `unsigned char`, сбрасываясь в 0 после 255 и начиная круг заново. Таким образом, условие i < 256 всегда истинно, и цикл становится бесконечным.

# Задача 3: на обманку типов данных

`#include <iostream>`

`int main()`
`{`
    `int a = 0;`
    `const int& ra = a;`
    `const double& dra = a; //`
    `a++;`
    `std::cout << a;`
    `std::cout << ra;`
    `std::cout << dra;`
`}`

Подвох в том, что `const double& dra = a;` создаёт временный объект типа `double`, инициализированный значением a на момент привязки (то есть нулём). Ссылка `dra` привязывается именно к этому временному объекту, а не к самой переменной `a`, поэтому последующий инкремент `a++` на него не влияет — `dra` так и остаётся хранить 0.0. Отсюда и вывод: `a == 1`, `ra == 1` (ссылка на a напрямую), `dra == 0`.

# ООП: Задача 1. Что выведет данный код в консоль?

```
#include <iostream>

class MyClass
{
  public:
    MyClass() : value(1)
    {
        value = 2;
    }

    int getValue() const noexcept
    {
        return value;
    }

  private:
    int value = 3;
};

int main()
{
    MyClass myObject;
    std::cout << myObject.getValue() << std::endl;
    return 0;
}
```

`выведет 2`

# ООП: Задача 2. Что выведет данный код в консоль?

```
#include <iostream>

class MyClass
{
  public:
    MyClass() = default;

    void set(const int newValue) const {
        _value = newValue;
    }

    void print() const {
        std::cout << _value << std::endl;
    }

  private:
    int _value = 5;
};

int main()
{
    MyClass myObject;
    myObject.set(42); 
    myObject.print();
}
```

`будет ошибка компиляции, тк у константного метода нельзя производить изменения данных класса`

# ООП: Задача 3. Что выведет данный код в консоль?

```
#include <iostream>

class BaseClass {
  public:
    BaseClass() {
      std::cout << "BaseClass()\n";
        print();
    }

    virtual ~BaseClass()
    {
      std::cout << "~BaseClass()\n";
    }

    virtual void print() {
        std::cout << "base" << std::endl;
    }
};

class DerivedClass : public BaseClass {
  public:
    DerivedClass() : BaseClass() {
      std::cout << "DerivedClass()\n";
    }
    
    ~DerivedClass() override {
      std::cout << "~DerivedClass()\n";
    }

    void print() override {
        std::cout << "derived" << std::endl;
    }
};

int main() {
    BaseClass* ptr = new DerivedClass;
    ptr->print();
    delete ptr;
}
```
```
ptr будет указывать на данные производого класса, потому при вызове ptr выведется "derived". 
А весь вывод следующий:
    "BaseClass()\n";
    "base"
    "DerivedClass()\n";
    "derived" 
    "~DerivedClass()\n";
    "~BaseClass()\n";
```

# ООП Задача 4. Что выведет данный код в консоль?

```
#include <iostream>
#include <exception>

static int x = 0;

class A {
  public:
    A() {
        std::cout << 'a';
        if (x++ == 0) {
            throw std::exception();
        }
    }
    ~A() { std::cout << 'A'; }
};

class B {
  public:
    B() { std::cout << 'b'; }
    ~B() { std::cout << 'B'; }

    A a;
};

void foo() { static B b; }

int main() {
    try {
        foo();
    } catch (std::exception &) {
        std::cout << 'c';
        foo();
    }
    return 0;
}
```

``` 
При вызове foo в блоке try у нас начнет создаваться объект класса B. Сначала проинициализируются поля этого класса/структуры, а затем уже вызовется конструктор. Но в данном случае,
у нас выскочит исключение из объекта А, потому А будет не конца сконструирован. Как следствие, объект класса B также будет не до конца сконструирован. Как итог, в catch мы ловим исключение
и еще раз пытаемся создать объект. В итоге порядок вывода у нас такой:
'a' 'c' 'a' 'b' 'B' 'A'
```

# ООП Задача 5. Что выведет данный код в консоль?

```
#include <iostream>

struct A {
    A() { std::cout << "A "; }
    A(const A&) { std::cout << "A& "; }
    A& operator=(const A&) { std::cout << "=A& "; return *this; }
    ~A() { std::cout << "~A "; }
};

A createA() {
    A a; // NRVO
    return a;
}

int main() {
    A a = createA();
    return 0;
}
```

`Здесь у нас есть NRVO, значит операторы копирования присваиванием и конструктор копирования не будут использоваться. В итоге вывод будет просто "A " "~A "`

# ООП Задача 9. Что выведет данный код в консоль?

```
struct A
{
    A() { std::cout << "A "; }
    A(const A &) { std::cout << "A_copy "; }
    A(A &&) { std::cout << "A_move "; }
    int data = 0;
};

struct B
{
    A value;
    
    B() { std::cout << "B "; }
    B(const B & other)
        : value(other.value)
    {
        std::cout << "B_copy ";
    }
    B(B && other)
        : value(other.value)
    {
        std::cout << "B_move ";
    }
};

void out_b(B && b)
{
    std::cout << b.value.data;
}

int main()
{
    B b1; // ?
    
    B b2{b1}; // ?
    
    B b3(std::move(b1)); // ?
    
    out_b(std::move(b3)); // ?
    
    return 0;
}
```

``` Здесь проверяется знания на то как устроен перемещающий конструктор + семантика перемещения. В крацах, вывод будет следующим:
"A " "B "
"A_copy " "B_copy "
"A_copy " "B_move "
0
```

# ООП Задача 10. Что выведет данный код в консоль?

```
#include <iostream>

struct A
{
    virtual void f() { std::cout << "A\n"; }
};

struct B : public A
{
    void f() { std::cout << "B\n"; } // здесь срабатывает перегрузка ( типо компилятор по умолчанию думает что это перегрузка тк мы отнаследовались + у нас сигнатуры совпадают )
};

void f1(A *obj)
{
    obj->f();
}

void f2(A obj)
{
    obj.f(); // Здесь вызовется "A\n", тк мы передаем по значению и у нас часть памяти отвечающая за B отсекается
}

void f3(A& obj)
{
    obj.f(); // здесь мы разыменовываем в main указатель, а затем берем ссылку на область памяти от "типо переменной". Как итог, ссылка ссылается на область памяти типа A но содержит данные по B и вызовется B\n"
}

int main()
{
    A* a = new B();

    // output?
    a->f();      // ?
    f1(a);       // ?
    f2(*a);      // ?
    f3(*a);      // ?

    return 0;
}
```

``` Основной момент я уже описал в коментарии. Плюс тут также a будет иметь данные b, ничего не обрезается. Теперь по выводам
"B\n"
"B\n"
"A\n"
B\n"
```

# ООП: Задача 12. Что выведется в консоль?

```
void foo(std::function<void(int)> func){
  func(10);
}

int main(){
  int a = 0; 
  auto f = [a](int x) mutable {
    std::cout << a << ' ';
    a += x;
  };

  //auto f = [&a](int x) {
  //  std::cout << a << ' ';
  //  a += x;
  //};
  
  f(5);
  f(5);

  foo(f);
  
  std::cout << a << '\n';
}
```

```
в случае с параметром который копируется, у нас он копируется во внутреннее поле анонимного класса и потому выведется 0 5 10 0. 
первый вызов 0, а+=5
второй вызов 5 а += 5
третий вызов 10 а += 10 ( но у нас увеличивается значение внутренней переменной а из анонимного класса )
четвертый выведет значение а из main ( 0 )

во втором случае вывод будет 0 5 10 10 потому что у нас происходит копирование по ссылке
первый вызов 0, а += 5
второй вызов 5, а += 5
в третьем вызове у нас обертка используется, туда копируется наше состояние из лямбды и получается что мы выводи 10, и прибавляем к внутренней переменной обертки 10. а наш лямбда не изменилась
ну и в четвертом случае выведется 10 тк это локальная переменная из main была передана по ссылке, но у нас все равно использовались внутренние переменные анонимного класса
итого 0 5 10 10
```