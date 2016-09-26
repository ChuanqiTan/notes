***********************
Python高级编程
***********************


第一章：准备工作
=======================

- | Python的交互式命令行工具会在启动时查找环境变量PYTHONSTARTUP，并执行该变量中所指定的文件里的程序代码。
  | 如一般的添加自动补全的功能readline.parse_and_bind('tab: complete')。
- iPython是一个增强型的命令行工具。 
- Python中的setuptools相当于Debian中的apt，easy_install就是调用setuptools的工具。


第二章：语法最佳实现-低于类级
=======================================
- 每当要对序列中的内容进行循环处理时，就应该尝试用 **列表推导式**
- **迭代器** 和 **生成器** ,现代语言很多都有生成器，使用关键字 **yield** ::

    """ 迭代器的约定在于：
            next()方法返回下一个元素
            迭代完成后抛出StopIteration异常
            __iter__()方式返回迭代器本身
    """
    class MyIterator(object):
        def __init__(self):
            self.i = 0
            
        def next(self):
            if self.i > 10:
                return StopIteration

            self.i += 2
            return self.i
        
        def __iter__(self):
            return self
    
    [i for i in MyIterator()]      

    """生成器返回一个特殊的对象：generator对象,它知道如何保存正在执行的环境。
    """
    def f():
        i = 0
        while True:
            i += 1
            yield i

    my_iter = f()
    [my_iter.next() for i in range(5)]

  >>> [2, 4, 6, 8, 10]
  >>> [1, 2, 3, 4, 5]

  生成器的工作原理是：
    每次遇到yield时，就相当于函数返回值似的返回这个值并保存当前的运行状态；当对应的迭代器再次被调用next()时，就恢复保存的状态并继续运行。

  一次返回一个元素，在很多时候可以提高整体性能，不必像传统迭代方式那样一次完成所有的计算。
- **输入式生成器** 
    使用 **(yield)** 来转换为输入式生成器，等待 **send()方法** 传递参数再继续执行::

        >>> def f():
        ...   while True:
        ...     i = (yield)
        ...     print i
        ... 
        >>> a=f()
        >>> a.next()
        >>> a.send(45)
        45
        >>> a.send(445)
        445

  | send(123)方法相当于将(yield)赋值为123再调用next()继续。同理还有2个姐妹方法 **throw()** , **close()** 。
  | throw()相当于抛出一个异常再调用next()继续，而close()相当于抛出GeneratorExit异常再调用next()继续。

  GeneratorExit异常在生成器中无法捕获，因为编译器需要用它来确定调用close()时是否正常退出。所以如果代码与这个异常关联，那么解释程序将抛出一个系统错误并退出。
- **生成器表达式** ：类型于列表推导式，用圆括号代替中括号。
    它和列表解析的语法很像，但是在大数据量处理时，生成器表达式的优势就体现出来了，因为它的内存使用方式更好，效率更高， **它并不创建一个列表，只是返回一个生成器** 。

  >>> (i + 1 for i in range(10) if i % 2)
  <generator object <genexpr> at 0x011DC5D0>

- **装饰器** : 它是函数和方法的封装（接收一个函数并返回增强版本的新函数）::

      def mydec(i):
          def _mydec2(func):
              def __mydec3(*argv, **kw):
                  print "Begin", i
                  res = func(*argv, **kw)
                  print "End"
                  return res
              return __mydec3
          return _mydec2
     
      @mydec(4)
      def MyF1():
          print "MyF1() body..."
     
      @mydec(9)
      def MyF2():
          print "MyF2() body..."
     
      MyF1()
      MyF2()
     
  >>> Begin 4
  >>> MyF1() body...
  >>> End
  >>> Begin 9
  >>> MyF2() body...
  >>> End

  装饰器应该关注于所封装的函数或方法接收和返回的参数，如果需要，应该尽可能限制其内省工作。
- with语法，解决资源释放问题的新语法，相当于 ``try...expect...finally...`` 的简写形式::

    class Context(object):
        def __enter__(self):
            print "Enter ..."
        def __exit__(self, exception_type, exception_value, exception_traceback):
            print "Leaving ..."

    with Context():
        print "I am in zone..."

  >>> Enter ...
  >>> I am in zone...
  >>> Leaving ...

  能够使用with语句来处理的类就是满足with协议的类，即实现了 ``__enter__`` , ``__exit__`` 两个方法。


第三章：语法最佳实现-类级
=======================================
- 最佳实践

  - 避免使用多重继承
  - super的使用必须一致，大家都倾向于不使用super，我也认为传统的根据类名来调用比较好，super带来的坏处大于好处
  - 不要混用老式的和新式的类，因为它们的MRO（方法解析顺序）不同
  - 调用父类时，为了避免出现问题，快速的使用__mro__检查一下类层次

- 在Python中，类的私有属性是用前导_来实现命名改编的
- **描述符** 定义在引用一个对象的特征时所应该完成的事情，其实非常简单易解，就是实现了三个特殊的方法的类。
  __get__在特性被读取时调用；__set__在特性被赋值时调用；__del__在特征被del时调用。
  示例代码如下::

    class UpperString(object):
        def __init__(self):
            self.value = ''
        def __get__(self, instance, klass):
            return self.value
        def __set__(self, instance, value):
            self.value = value.upper()

    class MyClass(object):
        my_attr = UpperString()

    a_instance = MyClass()
    a_instance.my_attr = "tanchuanqi"
    print a_instance.my_attr

  >>> TANCHUANQI

- **属性** 把几个方法合并成一个属性，很好理解，也都是语法糖::

    class MyClass(object):
        def __init__(self):
            self.v = 0
        def _v_get(self):
            return self.v
        def _v_set(self, value)
            self.v = value
        def _v_delete(self):
            print "del self.v"

        my_property = property(_v_get, _v_set, _v_delete, "This is doc string")

  属性有一点不直观的就是：property()只会绑定当前类中的方法，绝不会绑定派生类中的方法，无论派生类是否重载了相关的函数::

    class FirstClass(object):
        def _get_v(self):
            return "FirstClass"
        value = property(_get_v)

    class SecondClass(FirstClass):
        def _get_v(self):
            return "SecondClass"
        #value = property(_get_v)         重新定义一次value property是解决办法

    SecondClass().value

  >>> 'FirstClass'

  这不合逻辑，所以不要在派生类中重载被关联为property的方法。解决这个问题的办法是再SecondClass中再重新定义一次value property。
- **槽** 极少使用，它允许使用__solts__特性来为指定的类设置一个静态列表，并且跳过每个类实例中__dict__列表的创建工作。
- **__new__方法** 它是特殊的元构造程序，与__init__不同的地方在于它一定会被调用，子类初始化时也会调用父类的__new__方法。
  所以，很多初始化的工作都应该放在__new__方法中处理。
- **type 动态生成类型** 内建类型type是内建的基本工厂::

    def method(self):
        return 1

    klass = type('MyClass', (object,), {'method':method})
    instance = klass()
    print instance.method

  >>> 1

- **__metaclass__方法** 设置类级别的在类型创建时的操作::

    def equip(classname, base_types, dict):
        pass

    class MyClass(object):
        __metaclass__ = equip
        pass

  任何情况下都要记得，__metaclass__和其它的动态处理类的方法都要谨慎使用，很容易使类的结构变的一团糟！

  
第四章：选择好的名称
=======================================
- 命名风格：

  - 常量：使用大写+下划线的形式(常量最好统一放在包中的一个独立文件，像Django的config.py)
  - 变量：使用小写+下划线的形式
  - 函数和方法：也应该使用小写+下划线的风格
  - 属性：也是小写+下划线的形式
  - 特殊的方法(__str__,__item__,__repr__, ...)应该被放在类定义的最前面
  - 类名：应该总是使用CamelCase的命名风格，当定义模块的私有类时，使用前导下划线
  - 模块和包：除__init__外，模块名称都应该使用 **不带下划线的** 小写字母命名

- 私有元素用一个前导下划线标记_private，私有的变量、方法、类名、模块或包都应该用前导下划线标示为私有。

  私有元素的争论：
    一个前导下划线是约定为私有元素，而2个前导下划线则会强制进行命名改编(name mailing) 。所以很多人使用2个前导下划线来标识私有元素。
    这其实是不合适的，因为 **python中的name mailing的动机不是为了提供私有机制，而是为了确保基类隐式地避免子类中的冲突** ::

        >>> class A:
        ...   def _abc(self):
        ...     pass
        ... 
        >>> dir(A)
        ['__doc__', '__module__', '_abc']
        >>> class B:
        ...   def __abc(self):
        ...     pass
        ... 
        >>> dir(B)
        ['_B__abc', '__doc__', '__module__']

    所以，正确的方法是使用1个前导下划线，而不是用2个来画蛇添足，因为2个前导下划线也同样保证不了私有机制。
- 参数设计的3原则：

  - 根据设计来构建参数，即必须站在用户的角度来进行参数的设计。
  - 在任何情况下，断言assert都必须小心的进行，并且不应该导致Python变成一种静态类型的语言。
      唯一的使用场景就是保护代码不被无意义的调用。
  - 小心使用*args和**kw魔法参数，如果你觉得现在必须使用魔法参数，那么一般意味着这个方法需要被分解或重构！
  - 类及它的特性之间应当避免冗余，如SMTP.smtp_send()就是冗余，正确的命名应该是SMTP.send()

- 设计API的原则：

  - 避免冗长，形成高级接口和低级接口的组合
  - 构建命名空间树
  - 分解代码：一个函数不应该超过一个屏幕；类的方法一般不超过10个；一个模块一般不超过500行；
  - 使用Egg：为了避免整个代码库都在一个目录下，并能够单独发布每个包，就可以使用Egg。它提供了构建"命名空间的包"的简单方法，就像Java中的JAR一样。
  - 使用deprecation过程（及warning模块）

