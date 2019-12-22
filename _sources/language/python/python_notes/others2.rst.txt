其它
##############

编码问题
++++++++++++++++++++++

Python2.x中的编码问题
==================

   | 字符串在Python内部的表示是unicode编码\ ，因此，在做编码转换时，通常需要以unicode作为中间编码，即先\ 将其他编码的字符串解码（decode）成unicode，再从unicode编码（encode）成另一种编码\ 。
   | 但是，\ Python 2.x的默认编码格式是ASCII（因为python诞生比unicode要早）\ ，就是说，在没有指定Python源码编码格式的情况下，源码中的所有字符都会被默认为ASCII码。也因为这个根本原因，在Python 2.x中经常会遇到UnicodeDecodeError或者UnicodeEncodeError的异常。

   | 为了能够处理Unicode数据，同时兼容Python某些内部模块，\ Python 2.x中提供了Unicode这种数据类型\ ，通过decode和encode方法可以将其它编码和Unicode编码相互转化，但同时也引入了UnicodeDecodeError和UnicodeEncodeError异常。
   | 如果在文件头部没有指定文件编码类型，那么文件里的字符串字面值就是 ascii，否则就是指定的 coding 类型\ 。

   切记，unicode是python内部表示字符串的数据类型，py内部只理解unicode，所以：

-  对于非unicode编码（py内部不能原生理解的编码），就需要进行解码，所以decode是从str 到 unicode，解码的结果就是py能理解的unicode。

-  encode是从 unicode 到 str，编码就是从内部表示法到其它表示方法。

..

   str和unicode

   str和unicode都是basestring的子类\ 。严格意义上说，\ str其实是字节串\ ，它是unicode经过编码后的字节组成的序列。对UTF-8编码的str'汉'使用len()函数时，结果是3，因为实际上，UTF-8编码的'汉' == '\xE6\xB1\x89'。

   unicode才是真正意义上的字符串，对字节串str使用正确的字符编码进行解码后获得，并且len(u'汉') == 1。

   再来看看\ encode()和decode()两个basestring的实例方法\ ，理解了str和unicode的区别后，这两个方法就不会再混淆了::

    1  # coding: UTF-8
    2
    3  u = u'汉'
    4  print repr(u) # u'\u6c49'
    5  s = u.encode('UTF-8')
    6  print repr(s) # '\xe6\xb1\x89'
    7  u2 = s.decode('UTF-8')
    8  print repr(u2) # u'\u6c49'
    9
    10 # 对unicode进行解码是错误的
    11 # s2 = u.decode('UTF-8')
    12 # 同样，对str进行编码也是错误的
    13 # u2 = s.encode('UTF-8')

   需要注意的是，虽然对str调用encode()方法是错误的，但实际上Python不会抛出异常，而是返回另外一个相同内容但不同id的str；对unicode调用decode()方法也是这样。很不理解为什么不把encode()和decode()分别放在unicode和str中而是都放在basestring中，但既然已经这样了，我们就小心避免犯错吧。

PYTHON-进阶-编码处理小结
========================

-  `Python-进阶-编码处理小结 <http://wklken.me/posts/2013/08/31/python-extra-coding-intro.html>`__

-  `开始 <http://wklken.me/posts/2013/08/31/python-extra-coding-intro.html#_1>`__

-  `首先 <http://wklken.me/posts/2013/08/31/python-extra-coding-intro.html#_2>`__

-  `str 和 unicode <http://wklken.me/posts/2013/08/31/python-extra-coding-intro.html#str-unicode>`__

-  `文件处理,IDE和控制台 <http://wklken.me/posts/2013/08/31/python-extra-coding-intro.html#ide>`__

-  `建议 <http://wklken.me/posts/2013/08/31/python-extra-coding-intro.html#_3>`__

-  `相关模块及一些方法 <http://wklken.me/posts/2013/08/31/python-extra-coding-intro.html#_4>`__

..

   整理下python编码相关的内容

   注意: 以下讨论为Python2.x版本, Py3k的待尝试

   开始

   用python处理中文时，读取文件或消息，http参数等等

   一运行，发现乱码(字符串处理，读写文件，print)

   然后，大多数人的做法是，调用encode/decode进行调试，并没有明确思考为何出现乱码

   所以调试时最常出现的错误

   错误1

   | Traceback (most recent call last):
   | File "<stdin>", line 1, in <module>
   | UnicodeDecodeError: 'ascii' codec can't decode byte 0xe6 in position 0: ordinal not in range(128)

   错误2

   | Traceback (most recent call last):
   | File "<stdin>", line 1, in <module>
   | File "/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/encodings/utf_8.py", line 16, in decode
   | return codecs.utf_8_decode(input, errors, True)
   | UnicodeEncodeError: 'ascii' codec can't encode characters in position 0-1: ordinal not in range(128)

   首先

   必须有大体概念，了解下字符集，\ `字符编码 <http://zh.wikipedia.org/wiki/%E5%AD%97%E7%AC%A6%E7%BC%96%E7%A0%81>`__

   `ASCII <http://zh.wikipedia.org/zh/ASCII>`__ | `Unicode <http://zh.wikipedia.org/zh/Unicode>`__ | `UTF-8 <http://zh.wikipedia.org/zh/UTF-8>`__ \| 等等

   `字符编码笔记：ASCII，Unicode和UTF-8 <http://www.ruanyifeng.com/blog/2007/10/ascii_unicode_and_utf-8.html>`__

   `淘宝搜索技术博客-中文编码杂谈 <http://www.searchtb.com/2012/04/chinese_encode.html>`__

   str 和 unicode

   str和unicode都是basestring的子类

   所以有判断是否是字符串的方法

   | def is_str(s):
   | return isinstance(s, basestring)

   str和unicode 转换

   decode \ `文档 <http://www.tutorialspoint.com/python/string_decode.htm>`__

   encode \ `文档 <http://www.tutorialspoint.com/python/string_encode.htm>`__

   | str -> decode('the_coding_of_str') -> unicode
   | unicode -> encode('the_coding_you_want') -> str

   区别

   str是字节串，由unicode经过编码(encode)后的字节组成的

   声明方式

   | s = '中文'
   | s = u'中文'.encode('utf-8')

   | >>> type('中文')
   | <type 'str'>

   求长度(返回字节数)

   | >>> u'中文'.encode('utf-8')
   | '\xe4\xb8\xad\xe6\x96\x87'
   | >>> len(u'中文'.encode('utf-8'))
   | 6

   unicode才是真正意义上的字符串，由字符组成

   声明方式

   | s = u'中文'
   | s = '中文'.decode('utf-8')
   | s = unicode('中文', 'utf-8')

   | >>> type(u'中文')
   | <type 'unicode'>

   求长度(返回字符数),在逻辑中真正想要用的

   | >>> u'中文'
   | u'\u4e2d\u6587'
   | >>> len(u'中文')
   | 2

   结论

   搞明白要处理的是str还是unicode, 使用对的处理方法(str.decode/unicode.encode)

   下面是判断是否为unicode/str的方法

   | >>> isinstance(u'中文', unicode)
   | True
   | >>> isinstance('中文', unicode)
   | False

   | >>> isinstance('中文', str)
   | True
   | >>> isinstance(u'中文', str)
   | False

   简单原则：不要对str使用encode，不要对unicode使用decode (事实上可以对str进行encode的，具体见最后，为了保证简单，不建议)

   | >>> '中文'.encode('utf-8')
   | Traceback (most recent call last):
   | File "<stdin>", line 1, in <module>
   | UnicodeDecodeError: 'ascii' codec can't decode byte 0xe4 in position 0: ordinal not in range(128)

   | >>> u'中文'.decode('utf-8')
   | Traceback (most recent call last):
   | File "<stdin>", line 1, in <module>
   | File "/System/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/encodings/utf_8.py", line 16, in decode
   | return codecs.utf_8_decode(input, errors, True)
   | UnicodeEncodeError: 'ascii' codec can't encode characters in position 0-1: ordinal not in range(128)

   不同编码转换,使用unicode作为中间编码

   | #s是code_A的str
   | s.decode('code_A').encode('code_B')

   文件处理,IDE和控制台

   处理流程，可以这么使用，把python看做一个水池，一个入口，一个出口

   入口处，全部转成unicode, 池里全部使用unicode处理，出口处，再转成目标编码(当然，有例外，处理逻辑中要用到具体编码的情况)

   读文件

   外部输入编码，decode转成unicode

   处理(内部编码，统一unicode)

   encode转成需要的目标编码

   写到目标输出(文件或控制台)

   IDE和控制台报错，原因是print时，编码和IDE自身编码不一致导致

   输出时将编码转换成一致的就可以正常输出

   | >>> print u'中文'.encode('gbk')
   | >>> print u'中文'.encode('utf-8')
   | 中文

   建议

   规范编码

   统一编码，防止由于某个环节产生的乱码

   环境编码，IDE/文本编辑器, 文件编码，数据库数据表编码

   保证代码源文件编码

   这个很重要

   py文件默认编码是ASCII, 在源代码文件中，如果用到非ASCII字符，需要在文件头部进行编码声明 \ `文档 <http://www.python.org/dev/peps/pep-0263/>`__

   不声明的话，输入非ASCII会遇到的错误,必须放在文件第一行或第二行

   | File "XXX.py", line 3
   | SyntaxError: Non-ASCII character '\xd6' in file c\ .py on line 3, but no encoding declared; see `http://www.python.org/\ peps/pep-0263.html <http://www.python.org/peps/pep-0263.html>`__ for details

   声明方法

   | # -- coding: utf-8 --
   | 或者
   | #coding=utf-8

   若头部声明coding=utf-8, a = '中文' 其编码为utf-8

   若头部声明coding=gb2312, a = '中文' 其编码为gbk

   so, 同一项目中所有源文件头部统一一个编码,并且声明的编码要和源文件保存的编码一致(编辑器相关)

   在源代码用作处理的硬编码字符串，统一用unicode

   将其类型和源文件本身的编码隔离开, 独立无依赖方便流程中各个位置处理

   | if s == u'中文': #而不是 s == '中文'
   | pass
   | #注意这里 s到这里时，确保转为unicode

   以上几步搞定后，你只需要关注两个 unicode和 你设定的编码(一般使用utf-8)

   处理顺序

   | 1. Decode early
   | 2. Unicode everywhere
   | 3. Encode later

   相关模块及一些方法

   获得和设置系统默认编码

   | >>> import sys
   | >>> sys.getdefaultencoding()
   | 'ascii'

   | >>> reload(sys)
   | <module 'sys' (built-in)>
   | >>> sys.setdefaultencoding('utf-8')
   | >>> sys.getdefaultencoding()
   | 'utf-8'

   str.encode('other_coding')

   在python中，直接将某种编码的str进行encode成另一种编码str

   | #str_A为utf-8
   | str_A.encode('gbk')

   | 执行的操作是
   | str_A.decode('sys_codec').encode('gbk')
   | 这里sys_codec即为上一步 sys.getdefaultencoding() 的编码

   '获得和设置系统默认编码'和这里的str.encode是相关的，但我一般很少这么用，主要是觉得复杂不可控,还是输入明确decode，输出明确encode来得简单些(个人观点)

   chardet

   文件编码检测，\ `下载 <https://pypi.python.org/pypi/chardet>`__

   | >>> import chardet
   | >>> f = open('test.txt','r')
   | >>> result = chardet.detect(f.read())
   | >>> result
   | {'confidence': 0.99, 'encoding': 'utf-8'}

   \\u字符串转对应unicode字符串

   | >>> u'中'
   | u'\u4e2d'

   | >>> s = '\u4e2d'
   | >>> print s.decode('unicode_escape')
   | 中

   | >>> a = '`\\\u4fee\\u6539\\u8282\\u70b9\\u72b6\\u6001\\u6210\\u529f <file://u4fee/u6539/u8282/u70b9/u72b6/u6001/u6210/u529f>`__'
   | >>> a.decode('unicode_escape')
   | u'\u4fee\u6539\u8282\u70b9\u72b6\u6001\u6210\u529f'

   python unicode文档

   `入口 <http://docs.python.org/2/tutorial/introduction.html#unicode-strings>`__

   好了，暂时就这么多，希望讲清楚了

   thx

   wklken

   2013-08-31 于深圳

Python的中文编码问题
====================

   字符串是Python中最常用的数据类型，而且很多时候你会用到一些不属于标准ASCII字符集的字符，这时候代码就很可能抛出UnicodeDecodeError: 'ascii' codec can't decode byte 0xc4 in position 10: ordinal not in range(128)异常。这种异常在Python中很容易遇到，尤其是在Python2.x中，是一个很让初学者费解头疼的问题。不过，如果你理解了Python的Unicode，并在编码中遵循一定的原则，这种编码问题还是比较容易理解和解决的。

   字符串在Python内部的表示是unicode编码，因此，在做编码转换时，通常需要以unicode作为中间编码，即先将其他编码的字符串解码（decode）成unicode，再从unicode编码（encode）成另一种编码。但是，Python 2.x的默认编码格式是ASCII，就是说，在没有指定Python源码编码格式的情况下，源码中的所有字符都会被默认为ASCII码。也因为这个根本原因，在Python 2.x中经常会遇到UnicodeDecodeError或者UnicodeEncodeError的异常。

   关于Unicode

   Unicode是一种字符集，它为每一种现代或古代使用的文字系统中出现的每一个字符都提供了统一的序列号，规定了符号的二进制代码，但没有规定这个二进制代码应该如何存储。也就是说：Unicode的编码方式是固定的，但是实现方式根据不同的需要有跟多种，常见的有UTF-8、UTF-16和UTF-32等。

   为了能够处理Unicode数据，同时兼容Python某些内部模块，Python 2.x中提供了Unicode这种数据类型，通过decode和encode方法可以将其它编码和Unicode编码相互转化，但同时也引入了UnicodeDecodeError和UnicodeEncodeError异常。。

   常见的几种编码异常

   Python中常见的几种编码异常有SyntaxError: Non-ASCII character、UnicodeDecodeError和UnicodeEncodeError等\ 。下面依次举例说明一下：

   1、SyntaxError: Non-ASCII character

   这种异常最不容易出现，也最容易处理，主要原因是Python源码文件中有非ASCII字符，而且同时没有声明源码编码格式，例如：

   | s = '中文'
   | print s # 抛出异常

   2、UnicodeDecodeError

   这个异常有时候会在调用decode方法时出现，原因是Python打算将其他编码的字符转化为Unicode编码，但是字符本身的编码格式和decode方法传入的编码格式不一致，例如：

   | #!/usr/bin/python
   | # -- coding: utf-8 --
   | s = '中文'
   | s.decode('gb2312') # UnicodeDecodeError: 'gb2312' codec can't decode bytes in position 2-3: illegal multibyte sequence
   | print s

   上面这段代码中字符串s的编码格式是utf-8，但是在使用decode方法转化为Unicode编码时传入的参数是‘gb2312’，因此在转化的时候抛出UnicodeDecodeError异常。还有一种情况是在encode的时候：

   | #!/usr/bin/python
   | # -- coding: utf-8 --
   | s = '中文'
   | s.encode('gb2312') # UnicodeDecodeError: 'ascii' codec can't decode byte 0xe4 in position 0: ordinal not in range(128)
   | print s

   3、UnicodeEncodeError

   错误的使用decode和encode方法会出现这种异常，比如：使用decode方法将Unicode字符串转化的时候：

   | #!/usr/bin/python
   | # -- coding: utf-8 --
   | s = u'中文'
   | s.decode('utf-8') # UnicodeEncodeError: 'ascii' codec can't encode characters in position 0-1: ordinal not in range(128)
   | print s

   当然，除了上面列出的几种出现异常的情况之外还有很多可能出现异常的例子，这里就不在一一说明了。

   解决方法

   对于以上的几个异常，有以下几个处理的方法和原则。

   1、遵循PEP0263原则，声明编码格式

   在PEP 0263 -- Defining Python Source Code Encodings中提出了对Python编码问题的最基本的解决方法：在Python源码文件中声明编码格式，最常见的声明方式如下：

   | #!/usr/bin/python
   | # -- coding: <encoding name> --

   其中是代码所需要的编码格式，它可以是任意一种Python支持的格式，一般都会使用utf-8的编码格式。

   2、使用 u'中文' 替代 '中文'

   | str1 = '中文编码'
   | str2 = u'中文编码'

   Python中有以上两种声明字符串变量的方式，它们的主要区别是编码格式的不同，其中，str1的编码格式和Python文件声明的编码格式一致，而str2的编码格式则是Unicode。如果你要声明的字符串变量中存在非ASCII的字符，那么最好使用str2的声明格式，这样你就可以不需要执行decode，直接对字符串进行操作，可以避免一些出现异常的情况。

   3、Reset默认编码

   Python中出现这么多编码问题的根本原因是Python 2.x的默认编码格式是ASCII，所以你也可以通过以下的方式修改默认的编码格式：

   | import sys
   | sys.setdefaultencoding('utf-8')

   这种方法是可以解决部分编码问题，但是同时也会引入很多其他问题，得不偿失，不建议使用这种方式。

   4、终极原则：decode early, unicode everywhere, encode late

   最后分享一个终极原则：decode early, unicode everywhere, encode late，即：在输入或者声明字符串的时候，尽早地使用decode方法将字符串转化成unicode编码格式；然后在程序内使用字符串的时候统一使用unicode格式进行处理，比如字符串拼接、字符串替换、获取字符串的长度等操作；最后，在输出字符串的时候（控制台/网页/文件），通过encode方法将字符串转化为你所想要的编码格式，比如utf-8等。

   按照这个原则处理Python的字符串，基本上可以解决所有的编码问题（只要你的代码和Python环境没有问题）。。。

   5、升级Python 2.x到3.x

   额，最后一个方法，升级Python 2.x，使用Python 3.x版本。。这样说主要是为了吐槽Python 2.x的编码设计问题。当然，升级到Python 3.x肯定可以解决大部分因为编码产生的异常问题。毕竟Python 3.x版本对字符串这部分还是做了相当大的改进的，具体的下面会说。。。。

   Python 3.x中的Unicode

   在Python 3.0之后的版本中，所有的字符串都是使用Unicode编码的字符串序列，同时还有以下几个改进：

-  默认编码格式改为unicode

-  所有的Python内置模块都支持unicode

-  不再支持u'中文'的语法格式

..

   所以，对于Python 3.x来说，编码问题已经不再是个大的问题，基本上很少遇到上述的几个异常。关于Python 2.x str&unicode和Python 3.x str&bytes的更多说明和对比，大家可以看一下：Python中字符编码的总结和对比

   PS: 该文章转自我的博客：\ `Python的中文编码问题 <http://xianglong.me/article/learn-python-1-chinese-encoding/>`__

   Over!

CentOs 6.x 升级 Python 版本
++++++++++++++++++++

   文章目录

1.  `1. 在CentOS 6.X 上面安装 Python 2.7.X <https://ruiaylin.github.io/2014/12/12/python%20update/#在CentOS_6-X_上面安装_Python_2-7-X>`__

2.  `2. 升级步骤 <https://ruiaylin.github.io/2014/12/12/python%20update/#升级步骤>`__

3.  `2.1. 更新系统和开发工具集 <https://ruiaylin.github.io/2014/12/12/python%20update/#更新系统和开发工具集>`__

4.  `2.2. 源码安装Python 2.7.x <https://ruiaylin.github.io/2014/12/12/python%20update/#源码安装Python_2-7-x>`__

5.  `2.2.1. 安装详情： <https://ruiaylin.github.io/2014/12/12/python%20update/#安装详情：>`__

6.  `2.2.2. 设置 PATH <https://ruiaylin.github.io/2014/12/12/python%20update/#设置_PATH>`__

7.  `2.2.3. 安装 setuptools <https://ruiaylin.github.io/2014/12/12/python%20update/#安装_setuptools>`__

8.  `2.3. 安装 PIP <https://ruiaylin.github.io/2014/12/12/python%20update/#安装_PIP>`__

9.  `2.4. 修复 yum 工具 <https://ruiaylin.github.io/2014/12/12/python%20update/#修复_yum_工具>`__

10. `3. 总结 <https://ruiaylin.github.io/2014/12/12/python%20update/#总结>`__

..

   在CentOS 6.X 上面安装 Python 2.7.X

   CentOS 6.X 自带的python版本是 2.6 , 由于工作需要，很多时候需要2.7版本。所以需要进行版本升级。由于一些系统工具和服务是对 Python 有依赖的，所以升级 Python 版本需要注意。

   升级步骤

   如何欢乐的，没有痛苦的升级python版本 ，往下看 …

   更新系统和开发工具集

   更新指令

   | yum -y update
   | yum groupinstall -y 'development tools'

   另外还需要安装 python 工具需要的额外软件包 SSL, bz2, zlib

   yum install -y zlib-devel bzip2-devel openssl-devel xz-libs wget

   源码安装Python 2.7.x

   | wget http://www.python.org/ftp/python/2.7.8/Python-2.7.8.tar.xz
   | xz -d Python-2.7.8.tar.xz
   | tar -xvf Python-2.7.8.tar

   安装详情：

   | # 进入目录:
   | cd Python-2.7.8
   | # 运行配置 configure:
   | ./configure --prefix=/usr/local
   | # 编译安装:
   | make
   | make altinstall
   | # 检查 Python 版本:
   | [root@dbmasterxxx ~]# python2.7 -V
   | Python 2.7.8

   设置 PATH

   为了我们能够方便的使用Python，我们需要设置系统变量或者建立 软连接将新版本的 Python

   加入到 path 对应的目录 ：

   | export PATH="/usr/local/bin:$PATH"
   | or
   | ln -s /usr/local/bin/python2.7 /usr/bin/python
   | # 检查
   | [root@dbmasterxxx ~]# python -V
   | Python 2.7.8
   | [root@dbmasterxxx ~]# which python
   | /usr/bin/python

   安装 setuptools

   | #获取软件包
   | wget --no-check-certificate https://pypi.python.org/packages/source/s/setuptools/setuptools-1.4.2.tar.gz
   | # 解压:
   | tar -xvf setuptools-1.4.2.tar.gz
   | cd setuptools-1.4.2
   | # 使用 Python 2.7.8 安装 setuptools
   | python2.7 setup.py install

   安装 PIP

   curl https://bootstrap.pypa.io/get-pip.py \| python2.7 -

   这样出来的pip就默认会装到 2.7 的目录下了

   修复 yum 工具

   此时yum应该是失效的，因为此时默认python版本已经是2.7了。而yum需要的是2.6 所以：

   | [root@dbmasterxxx ~]# which yum
   | /usr/bin/yum
   | #修改 yum中的python
   | 将第一行 #!/usr/bin/python 改为 #!/usr/bin/python2.6
   | 此时yum就ok啦

   总结

   Python 版本升级过很多遍，每次都有问题，此方法来自互联网，经过使用，没有问题，特此总结一下

   来自 <\ https://ruiaylin.github.io/2014/12/12/python%20update/\ >
