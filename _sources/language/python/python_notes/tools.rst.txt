工具
#################

一些看着很爽的技巧：
+++++++++++++++++++++

   列表赋值： b = a[:]

   屏幕输出到文件：sys.stdout = open('log.txt','w')

   三元符号表示法： [STRIKEOUT:("no", "yes")[x == y]]\ ，不要用，用 "yes" if True else "No"

   链式比较：x < 10 < x10 < 100

   enumerate： for index, item in enumerate(a, 1)

   iter()可接收callable参数:

   iter()内建函数接收的参数分为两种，第一种是：

   iter(collection)---> iterator

   参数collection必须是可迭代对象或者是序列 ，第二种是：

   iter（callable， sentinel) --> iterator

   callable函数会一直被调用，直到它的返回结果等于sentinel

   列表步长： [::2]步长为2，[::-1] 列表反转

   For..else: 不break的话就执行else

   Try..else: 没有异常执行else里的语句

   合并列表： sum([[1, 2, 3], [4, 5, 6], [7, 8, 9]], [])

   内建模块： python -m http.server, python -m json.tool

   内建装饰器：

    -  偏函数： from functools import partial

    -  classmethod装饰器, 类方法(给人感觉非常类似于OC中的类方法), 其中第一个隐式参数为类

    -  staticmethod装饰器, 没有任何隐式参数. python中的静态方法类似与C++中的静态方法

    -  property装饰器

   函数式编程：map, reduce, filter

   内置函数：

       zip() 组合等长的可迭代对象

   定义枚举量::

       from enum import Enum
       Month = Enum('Month', ('Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'))

   使用slots减少内存开支

   漂亮的打印json: jons.dumps(j, indent=4)

让 Python 代码更易维护的七种武器
++++++++++++++

检查你的代码的质量，通过这些外部库使其更易维护。

可读性很重要。

— `Python 之禅 <https://link.zhihu.com/?target=https%3A//www.python.org/dev/peps/pep-0020/>`__\ \ (The Zen of Python)\ ，Tim Peters

随着软件项目进入“维护模式”，对可读性和编码标准的要求很容易落空（甚至从一开始就没有建立过那些标准）。然而，在代码库中保持一致的代码风格和测试标准能够显著减轻维护的压力，也能确保新的开发者能够快速了解项目的情况，同时能更好地全程保持应用程序的质量。

使用外部库来检查代码的质量不失为保护项目未来可维护性的一个好方法。以下会推荐一些我们最喜爱的\ `检查代码 <https://link.zhihu.com/?target=https%3A//en.wikipedia.org/wiki/Lint_%28software%29>`__\ （包括检查 PEP 8 和其它代码风格错误）的库，用它们来强制保持代码风格一致，并确保在项目成熟时有一个可接受的测试覆盖率。

检查你的代码风格

`PEP 8 <https://link.zhihu.com/?target=https%3A//www.python.org/dev/peps/pep-0008/>`__ 是 Python 代码风格规范，它规定了类似行长度、缩进、多行表达式、变量命名约定等内容。尽管你的团队自身可能也会有稍微不同于 PEP 8 的代码风格规范，但任何代码风格规范的目标都是在代码库中强制实施一致的标准，使代码的可读性更强、更易于维护。下面三个库就可以用来帮助你美化代码。

1、 Pylint

`Pylint <https://link.zhihu.com/?target=https%3A//www.pylint.org/>`__ 是一个检查违反 PEP 8 规范和常见错误的库。它在一些流行的\ `编辑器和 IDE <https://link.zhihu.com/?target=https%3A//pylint.readthedocs.io/en/latest/user_guide/ide-integration.html>`__ 中都有集成，也可以单独从命令行运行。

执行 pip install pylint 安装 Pylint 。然后运行 pylint [options] path/to/dir 或者 pylint [options] path/to/module.py 就可以在命令行中使用 Pylint，它会向控制台输出代码中违反规范和出现错误的地方。

你还可以使用 pylintrc \ `配置文件 <https://link.zhihu.com/?target=https%3A//pylint.readthedocs.io/en/latest/user_guide/run.html%23command-line-options>`__\ 来自定义 Pylint 对哪些代码错误进行检查。

2、 Flake8

`Flake8 <https://link.zhihu.com/?target=http%3A//flake8.pycqa.org/en/latest/>`__ 是“将 PEP 8、Pyflakes（类似 Pylint）、McCabe（代码复杂性检查器）和第三方插件整合到一起，以检查 Python 代码风格和质量的一个 Python 工具”。

执行 pip install flake8 安装 flake8 ，然后执行 flake8 [options] path/to/dir 或者 flake8 [options] path/to/module.py 可以查看报出的错误和警告。

和 Pylint 类似，Flake8 允许通过\ `配置文件 <https://link.zhihu.com/?target=http%3A//flake8.pycqa.org/en/latest/user/configuration.html%23configuration-locations>`__\ 来自定义检查的内容。它有非常清晰的文档，包括一些有用的\ `提交钩子 <https://link.zhihu.com/?target=http%3A//flake8.pycqa.org/en/latest/user/using-hooks.html>`__\ ，可以将自动检查代码纳入到开发工作流程之中。

Flake8 也可以集成到一些流行的编辑器和 IDE 当中，但在文档中并没有详细说明。要将 Flake8 集成到喜欢的编辑器或 IDE 中，可以搜索插件（例如 \ `Sublime Text 的 Flake8 插件 <https://link.zhihu.com/?target=https%3A//github.com/SublimeLinter/SublimeLinter-flake8>`__\ ）。

3、 Isort

`Isort <https://link.zhihu.com/?target=https%3A//github.com/timothycrosley/isort>`__ 这个库能将你在项目中导入的库按字母顺序排序，并将其`正确划分为不同部分 <https://link.zhihu.com/?target=https%3A//github.com/timothycrosley/isort%23how-does-isort-work>`__\ （例如标准库、第三方库、自建的库等）。这样提高了代码的可读性，并且可以在导入的库较多的时候轻松找到各个库。

执行 pip install isort 安装 isort，然后执行 isort path/to/module.py 就可以运行了。\ `文档 <https://link.zhihu.com/?target=https%3A//github.com/timothycrosley/isort%23using-isort>`__\ 中还提供了更多的配置项，例如通过\ `配置 <https://link.zhihu.com/?target=https%3A//github.com/timothycrosley/isort%23configuring-isort>`__ .isort.cfg 文件来决定 isort 如何处理一个库的多行导入。

和 Flake8、Pylint 一样，isort 也提供了将其与流行的\ `编辑器和 IDE <https://link.zhihu.com/?target=https%3A//github.com/timothycrosley/isort/wiki/isort-Plugins>`__ 集成的插件。

分享你的代码风格

每次文件发生变动之后都用命令行手动检查代码是一件痛苦的事，你可能也不太喜欢通过运行 IDE 中某个插件来实现这个功能。同样地，你的同事可能会用不同的代码检查方式，也许他们的编辑器中也没有那种插件，甚至你自己可能也不会严格检查代码和按照警告来更正代码。总之，你分享出来的代码库将会逐渐地变得混乱且难以阅读。

一个很好的解决方案是使用一个库，自动将代码按照 PEP 8 规范进行格式化。我们推荐的三个库都有不同的自定义级别来控制如何格式化代码。其中有一些设置较为特殊，例如 Pylint 和 Flake8 ，你需要先行测试，看看是否有你无法忍受但又不能修改的默认配置。

4、 Autopep8

`Autopep8 <https://link.zhihu.com/?target=https%3A//github.com/hhatto/autopep8>`__ 可以自动格式化指定的模块中的代码，包括重新缩进行、修复缩进、删除多余的空格，并重构常见的比较错误（例如布尔值和 None 值）。你可以查看文档中完整的`更正列表 <https://link.zhihu.com/?target=https%3A//github.com/hhatto/autopep8%23id4>`__\ 。

运行 pip install --upgrade autopep8 安装 Autopep8。然后执行 autopep8 --in-place --aggressive --aggressive <filename> 就可以重新格式化你的代码。aggressive 选项的数量表示 Auotopep8 在代码风格控制上有多少控制权。在这里可以详细了解 \ `aggressive <https://link.zhihu.com/?target=https%3A//github.com/hhatto/autopep8%23id5>`__ 选项。

5、 Yapf

`Yapf <https://link.zhihu.com/?target=https%3A//github.com/google/yapf>`__ 是另一种有自己的`配置项 <https://link.zhihu.com/?target=https%3A//github.com/google/yapf%23usage>`__\ 列表的重新格式化代码的工具。它与 Autopep8 的不同之处在于它不仅会指出代码中违反 PEP 8 规范的地方，还会对没有违反 PEP 8 但代码风格不一致的地方重新格式化，旨在令代码的可读性更强。

执行 pip install yapf 安装 Yapf，然后执行 yapf [options] path/to/dir 或 yapf [options] path/to/module.py 可以对代码重新格式化。\ `定制选项 <https://link.zhihu.com/?target=https%3A//github.com/google/yapf%23usage>`__\ 的完整列表在这里。

6、 Black

`Black <https://link.zhihu.com/?target=https%3A//github.com/ambv/black>`__ 在代码检查工具当中算是比较新的一个。它与 Autopep8 和 Yapf 类似，但限制较多，没有太多的自定义选项。这样的好处是你不需要去决定使用怎么样的代码风格，让 Black 来给你做决定就好。你可以在这里查阅 Black \ `有限的自定义选项 <https://link.zhihu.com/?target=https%3A//github.com/ambv/black%23command-line-options>`__\ 以及\ `如何在配置文件中对其进行设置 <https://link.zhihu.com/?target=https%3A//github.com/ambv/black%23pyprojecttoml>`__\ 。

Black 依赖于 Python 3.6+，但它可以格式化用 Python 2 编写的代码。执行 pip install black 安装 Black，然后执行 black path/to/dir 或 black path/to/module.py 就可以使用 Black 优化你的代码。

检查你的测试覆盖率

如果你正在进行编写测试，你需要确保提交到代码库的新代码都已经测试通过，并且不会降低测试覆盖率。虽然测试覆盖率不是衡量测试有效性和充分性的唯一指标，但它是确保项目遵循基本测试标准的一种方法。对于计算测试覆盖率，我们推荐使用 Coverage 这个库。

7、 Coverage

`Coverage <https://link.zhihu.com/?target=https%3A//coverage.readthedocs.io/en/latest/>`__ 有数种显示测试覆盖率的方式，包括将结果输出到控制台或 HTML 页面，并指出哪些具体哪些地方没有被覆盖到。你可以通过\ `配置文件 <https://link.zhihu.com/?target=https%3A//coverage.readthedocs.io/en/latest/config.html>`__\ 自定义 Coverage 检查的内容，让你更方便使用。

执行 pip install coverage 安装 Converage 。然后执行 coverage [path/to/module.py] [args] 可以运行程序并查看输出结果。如果要查看哪些代码行没有被覆盖，执行 coverage report -m 即可。

持续集成工具

持续集成(Continuous integration)\ （CI）是在合并和部署代码之前自动检查代码风格错误和测试覆盖率最小值的过程。很多免费或付费的工具都可以用于执行这项工作，具体的过程不在本文中赘述，但 CI 过程是令代码更易读和更易维护的重要步骤，关于这一部分可以参考 \ `Travis CI <https://link.zhihu.com/?target=https%3A//travis-ci.org/>`__ 和 `Jenkins <https://link.zhihu.com/?target=https%3A//jenkins.io/>`__\ 。

以上这些只是用于检查 Python 代码的各种工具中的其中几个。如果你有其它喜爱的工具，欢迎在评论中分享。

编译成so
+++++++++++++

把python源文件编译成so文件

亲测可用

前言

实际上属于一种代码混淆/加密的技术，大家知道python的源文件放在那里，大家是都可以看的，不像C语言编译出来可以拿编译后的东西去运行，所以就出现了这种需求。原理相当于将python编译成c，然后再转成.so文件

.so文件为动态连结库，可以在程序运行时动态链接，类似于windows的dll文件。

在网上搜了一下，常用的有2种方法：

-  通过gcc（make）来操作

-  使用python来操作 我用python来直接生成就够了，没有特殊需要别去折腾GCC

准备工作

-  在目录下创建__init__.py和hello.py

-  hello.py 内容为：

..

   | def hello():
   | print "hello"

使用python来操作

-  安装所需库CPython，命令如下：

..

   pip install cython

-  创建文件setup.py，内容如下：

..

   | from distutils.core import setup
   | from Cython.Build import cythonize
   | setup(
   | ext_modules = cythonize("hello.py")
   | )

-  执行setup.py文件 python setup.py build_ext --inplace

-  在当前目录下就生成了和当前目录同名的一个目录，进入目录即可看见so文件，打开so文件可见一些乱码，达到了加密的目的

Pip
++++++++++++++++++

名称来源于递归缩写：Pip installs Packages（PIP）

查看pip的安装目录：

   [chuanqi@iZu1v8f9z8gZ nginx]$ pip -V

   pip 8.1.2 from /usr/lib/python2.7/site-packages (python 2.7)

在虚拟环境中使用一下命令可以生成一个虚拟环境的安装包版本文件

   pip freeze > requirements.txt

   pip install -r requirements.txt

|pip_help|

virtualenv
+++++++++++++++

virtualenv的使用极其简单，2分钟就足够完全掌握了，基本上明白这些概念就足够了：

   virtualenv是提供完全隔离环境的库

   virtualenv 命令用来创建一个新的隔离环境

   virtualenv research # 创建名为research的隔离环境

   --no-site-packages 不包括site-packages里的包

   --system-packages 包括system-packages里的包

   --python 选择python版本

   cd research && source ./bin/active 激活隔离环境

   deactivate 退出隔离环境

virtualwrapper

   有一个virtualenvwrapper 是一个 virtualenv 虚拟环境的管理库，这个库可以更加方便的管理所有的虚拟环境。它的原理是把所有的虚拟环境都装在 WORKON_HOME 这个环境变量指定的目录下，这样就不用到处去找虚拟环境目录了，有一个统一的地方可以管理、查看。就这么简单的原理。

   用virtualenv，新建目录 ~/.virtualenv 然后把所有的隔离环境都放在这个目录下其实是一个道理。

   pip install virtualenvwrapper

   export WORKON_HOME=$HOME/.virtualenvs && source /usr/local/bin/virtualenvwrapper.sh

   lsvirtualenv -b # 列出虚拟环境

   workon [虚拟环境名称] # 切换虚拟环境

   lssitepackages # 查看环境里安装了哪些包

   cdvirtualenv [子目录名] # 进入当前环境的目录

   cpvirtualenv [source] [dest] # 复制虚拟环境

   deactivate # 退出虚拟环境

   rmvirtualenv [虚拟环境名称] # 删除虚拟环境

virtualenv 与 Anaconda 的冲突

   Anaconda 有自己的包管理方式，直接用pip安装virtualenv会出错，需要用conda安装virtualenv

   pip uninstall virtualenv

   conda install virtualenv

PyCharm 快捷键
++++++++++++++++++

============ =========
Command:     |image20|
============ =========
Ctrl         |image21|
Option (alt) |image22|
Shift        |image23|
============ =========

Mac OS X 10.5+ 的 Keymap 方案：

======== ======================= ================================================== ===========================================================
类别 快捷键              操作                                           备注
======== ======================= ================================================== ===========================================================
导航     Cmd + B, Cmd + Alt + B  跳转到声明/定义
         Cmd + [, Cmd + ]        上/下一个位置
         Ctrl + Tab              NB的Tab导航窗口
         Cmd + F12               显示文件Outline
         Cmd+ L                  跳到某行                                           Line
         Cmd + Shift + Backspace 跳到上一次编辑的位置
         Cmd + E                 最近文件列表
         Cmd + Shift + E         最近编辑文件列表

查找     Cmd+ Shift + O          查找文件                                           常用的三种查找都是O
         Cmd+ O                  查找类
         Cmd+ Alt+ O             查找符号
         双击 Shift              Search Everywhere                                  大杀器
         Cmd + F/R               当前文件搜索/替换
         Cmd + Shift+ F/R        全局搜索/替换
         Cmd+G, Cmd+Shift+G      下一个/上一个
         Alt + F7                find usage

编辑     Cmd + /                 注释/取消注释一行
         Cmd + Alt + L           代码块对齐
         Cmd + Backspace         删除当前行                                         Cmd + X 也一样
         Cmd+D                   在下一行复制本行的内容                             Duplicate
         Ctrl + Shift + J        合并两行                                           Joint
         Cmd +C                  复制光标当前行,剪切同理
         Cmd + Shift + 上/下     移动一条语句
         Alt + Shift + 上/下     移动一行代码
         Cmd+Z, Cmd+Shift+Z      撤销/重做
         Ctrl + O                重写方法                                           Overwrite

智能补全 Cmd + J                 代码块智能补全
         Alt + Cmd + T           指定代码被注释语句或者逻辑结构、函数包围
         Alt + /, Alt + ?        正反向的字符串匹配补全
         Alt + Space             快速定义                                           PyCharm有三种方式可以访问文档：快速定义，快速文档，外部文档
         Ctrl + J                快速文档 （直接F1好像也一样）
         Shift + F1              打开外部文档，非常牛啊，直接在浏览器中打开库的文档
         Cmd + P                 显示参数信息                                       Patameter

重构     Ctrl + T                弹出重构选择                                       好像跟 IdeaVim 冲突了
         Shift + F6              重命名
         Cmd+ F6                 重构签名

折叠     Cmd +                   展开当前
         Cmd -                   折叠当前
         Shift Cmd +             展开所有
         Shift Cmd -             折叠所有

运行调试 Ctrl + R                运行当前对象                                       Run
         Ctrl + Alt + R          选择一个对象并运行

其它     Alt + F12               打开 Terminal
         Alt + F1                选择一个子窗口为当前焦点
         Cmd+ W                  关闭当前标签
         Cmd+ Shift + A          查找并执行一个动作                                 Action 很多动作没有直接的快捷键，按名字查找很快捷
         Ctrl + Shift + 8        列选择模式                                         Alt + 鼠标选择更方便
======== ======================= ================================================== ===========================================================

熟练这些快捷键，再加上 IdeaVim 插件，我几乎就可以非常行云流水了！

|image25|

.. |pip_help| image:: media/image20.png
   :width: 8.66667in
   :height: 5.19792in

.. |image20| image:: media/image21.png
   :width: 0.1875in
   :height: 0.20833in
.. |image21| image:: media/image22.png
   :width: 0.17708in
   :height: 0.19792in
.. |image22| image:: media/image23.png
   :width: 0.1875in
   :height: 0.22917in
.. |image23| image:: media/image24.png
   :width: 0.1875in
   :height: 0.19792in
.. |image25| image:: media/image25.png
   :width: 13.32292in
   :height: 7.27083in
