
Dive Into Python 学习笔记
==============================
 
第二章：第一个Python程序 
----------------------------

::

    def buildConnectionString(params): 
        """Build a connection string from a dictionary of parameters. 
     
        Returns string.""" 
        return ";".join(["%s=%s" % (k, v) for k, v in params.items()]) 
     
    if __name__ == "__main__": 
        myParams = {"server":"mpilgrim", \ 
                    "database":"master", \ 
                    "uid":"sa", \ 
                    "pwd":"secret" \ 
                    } 
        print buildConnectionString(myParams) 

- ``def buildConnectionString(params)`` : 表示声明一个函数。 
- 三重引号：定义doc string，也是一种定义即包含单引号'又包含双引号"的字符串的简单方法。 
- 万物皆对象：连普通函数、模块等都是对象，可以这样 ``print buildConnectionString.__doc__`` 来打印函数的doc string。 
- Python使用代码缩进来代替{} ，这在其它语言都使用{}的时代来说真是种创新。
- 所有的模块都有一个内置属性 __name__，一个模块的 __name__ 的值取决于您如何应用模块，所以 ``if __name__ == "__main__":`` 被用来进行模块的单元测试。 

 
第三章：内置数据类型 
----------------------------

- Python内置的三种最常用的数据类型： 

    :Dictionary {}:  d = {"server":"mpilgrim", "database":"master"}  
    :List []:        l = ["a", "b", "mpilgrim", "z", "example"]  
    :Tuple ():       t = ("a", "b", "mpilgrim", "z", "example") 

- Dictionary类型于C++中的map：但是它是可以混用不同的数据类型的；del d["a"], d.clear()删除元素；keys(), values(), items()返回相应的list。
- | List很明显就类型于vector，如同vector对于C++的重要性，list可能是python中最常用的数据结构了！
  | 它可以使用负的坐标；分片Slice语法li[1:3], li[:3], li[2:], li[:]；搜索index("item"), 删除remove("item")，未找到对应的item时会抛出相应的异常。
  | 非常重要的一点是区分extend(扩展)、append(追加)操作的区别，append只在未尾添加仅仅一个元素，append一个list会把这个list作为一个子元素追加在未尾（长度变为n+1）；但是extend一个list时会把它的所有元素都一个个的添加到原list去（长度变为n+m）。
  | list也支持很多运算符语法： ``li = li + ["a", "b"], li += ["a", "b"], li = [1,2]*3`` （结果为[1,2,1,2,1,2]）
- | Tuple最大的特点就是“Tuple是不可变的！”，它也支持Slice语法，不可变的性质使得它速度很快，可以作为dictionary的key，可以使用z in t的语法查询一个元素是否在一个Tuple中。
  | tuple函数接收一个 list，并返回一个有着相同元素的 tuple。而list函数接收一个tuple返回一个list。
- 一次对多个元素进行赋值操作，同时使用range函数，非常酷： ``(MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY) = range(7)``
- 字符串的格式化: "%s=%d" % (k, v), 使用%进行字符串格式化时的选项与C语言中的printf一样丰富。
- 映射list：看2个例子就肯定能完全明白了::

    li = [elem*2 for elem in li]
    ["%s=%s" % (k, v) for k, v in params.items()]

- list的连接操作也是非常常用的 ``s = ";".join(li)`` ，逆操作是 ``s.split(";")``


第四章：自省的威力
----------------------------

::

    def info(object, spacing=10, collapse=1):   
        """Print methods and doc strings.
        
        Takes module, class, list, dictionary, or string."""
        methodList = [method for method in dir(object) if callable(getattr(object, method))]
        processFunc = collapse and (lambda s: " ".join(s.split())) or (lambda s: s)
        print "\n".join(["%s %s" % (method.ljust(spacing), processFunc(str(getattr(object, method).__doc__)))
                         for method in methodList])

- Python 有小部分相当有用的内置函数，归组到了 ``__builtin__`` 这个特殊的模块中。

  - type 函数返回任意对象的数据类型，type(getattr(object, method)) == types.FunctionType
  - str 将数据强制转换为字符串。每种数据类型都可以强制转换为字符串。
  - 强大的 dir 函数返回任意对象的属性和方法列表
  - callable 函数，它接收任何对象作为参数，如果参数对象是可调用的，返回 True；否则返回 False。

- 反射的核心是getattr, hasattr函数：getattr可以得到一个直到运行时才知道名称的对象的引用。
  ``getattr(li, "append")("Moe")``
- list过滤功能，与list的映射语法类型，只是在后面加上一个if语句：[elem for elem in li if len(elem) > 1]
- and 和 or 执行布尔逻辑演算，非常重要的一点是：“它们并不返回布尔值，而是返回它们实际进行比较的值之一”。
  由于它返回的是比较值之一，因此一般使用bool_expr and a or b来模拟?:三目操作符，但有时不一定有效，最安全的方法是(bool_expr and [a] or [b])[0]
- lambda表达式： ``g = lambda x: x*2``
  Python中lambda表达式与其它语言中的也十分想像，非常不同的一点就是lambda只能包含一个表达式，所以整个lambda只能占用一行，即:后面不允许换行。但是这才是正规的lambda表达式，C++中包含多行的lambda的正规名称应当是lambda函数。
- s.ljust(30)        ljust 用空格填充字符串以符合指定的长度


第五章：对象和面向对象
----------------------------

::

    import os, sys
    from UserDict import UserDict

    class FileInfo(UserDict):
        "store file metadata"
        def __init__(self, filename=None):
            UserDict.__init__(self)
            self["name"] = filename

    class MP3FileInfo(FileInfo):
        "store ID3v1.0 MP3 tags"
        tagDataMap = {"title"   : (  3,  33, stripnulls),
                      "artist"  : ( 33,  63, stripnulls),
                      "album"   : ( 63,  93, stripnulls),
                      "year"    : ( 93,  97, stripnulls),
                      "comment" : ( 97, 126, stripnulls),
                      "genre"   : (127, 128, ord)}

        def __parse(self, filename):
            "parse ID3v1.0 tags from MP3 file"
            self.clear()
            try:                               
                fsock = open(filename, "rb", 0)
                try:                           
                    fsock.seek(-128, 2)        
                    tagdata = fsock.read(128)  
                finally:                       
                    fsock.close()              
                if tagdata[:3] == "TAG":
                    for tag, (start, end, parseFunc) in self.tagDataMap.items():
                        self[tag] = parseFunc(tagdata[start:end])               
            except IOError:                    
                pass                           

        def __setitem__(self, key, item):
            if key == "name" and item:
                self.__parse(item)
            FileInfo.__setitem__(self, key, item)

- 区别 from MODULE import * 与 import MODULE，它们的区别在于是否会导入MODULE的符号到当前命令空间。
- Python 中，类的基类只是简单地列在类名后面的小括号里。
- __init__ 在类的实例创建后被立即调用，__init__ 是在 Python 中你可以得到的最接近构造函数的东西。但是这样严格来说是不正确的，是因为对象在调用 __init__ 时已经被构造出来了，你已经有了一个对类的新实例的有效引用。
- 每个类方法的第一个参数，包括 __init__，都是指向类的当前实例的引用。按照习惯这个参数总是被称为 self。注意self并不是一个关键字，但是它是一个非常坚固的习惯，应该严格的予以保持。
- __init__ 方法是可选的，但是一旦你定义了，就必须记得显示调用父类的 __init__ 方法 (如果它定义了的话)。
  这样更是正确的：无论何时子类想扩展父类的行为，后代方法必须在适当的时机，使用适当的参数，显式调用父类方法。
- 在 Python 中对类进行实例化很直接。要对类进行实例化，只要调用类 (就好像它是一个函数)。
- 习惯上，所有的数据属性都在 __init__ 方法中初始化为有意义的值。然而，这并不是必须的，因为数据属性，像局部变量一样，当你首次赋给它值的时候突然产生。
  应该总是在 __init__ 方法中给一个实例的所有数据属性赋予一个初始值。这样做将会节省你在后面调试的时，也是应当遵守的优秀编程习惯。
- Python自带的copy模块可以拷贝任意的python对象。
- Python只所有的方法都是可以被子类所覆盖的，可以这么想：所有的 Python 方法都是虚函数。
- 专用类方法：专用方法是在特殊情况下或当使用特别语法时由 Python 替你调用的，如：

  - __getitem__ : print a["abc"]
  - __setitem__ : a["abc"] = 3
  - __repr__    : 当调用 repr(instance) 时被调用。repr 函数是一个内置函数，它返回一个对象的字符串表示。
  - __cmp__     : 在比较类实例时被调用。
  - __len__     : 在调用 len(instance) 时被调用。
  - __delitem__ : 在调用 del instance[key] 时调用。
  - __call__    : 让一个类表现得像一个函数，允许你直接调用一个类实例。

- 对象的同一性和相等性，这在很多语言中都有涉及：

  - 同一性指的是两个对象指向完全相同的一个对象；
  - 相等性是指两个对象在某种意义上相等。
  - Java,C#类的语言使用==来表示同一性，而它们的Object类都派生了一个equals方法来表示相等性；
  - Python中使用a is b来表示同一性，而使用==来表示相等性。

- 区分“类属性”和“数据属性”，它们分别对应于C++中的“静态成员变量”和“普通成员变量”。

  - 类属性：直接类的内部，成员函数的外部进行定义的属性，如code中的tagDataMap;
  - 数据属性：通过直接赋值产生的属性，一定在 __init__ 成员方法中进行初始化。

- | Python 也有私有的概念，但Python中私有还是公有，完全取决于它的名字，以两个下划线开始 (但不是结束)，就表示它是私有的，其它所有的都是公有的。
  | 但是，实际上Python只是使用了一个小戏法，混淆了名字而已，例如私有方法A.__parse可以在外部通过_A__parse这个名字来方法，但永远不要去这么用。


第六章：异常与文件处理
----------------------------

- Python 使用 try...except...finally 来处理异常，使用 raise 来引发异常。
  与C++中的异常使用有一些独特之处在于可以能使用的范围更广，如导入模块：试着导入一个模块，导入一个并不存在的模块将引发一个 ImportError 异常。
  一个 try...except 块可以有一条 else 子句，就像 if 语句。如果在 try 块中没有异常引发，然后 else 子句被执行。
- 内置函数open用来打开在磁盘上的文件, 返回一个文件对象。然后就是几乎所有语言中都有的tell, seek, read, write, close方法。
- for循环：::

      for i in range(len(li))
      for k, v in os.environ.items()

- sys.modules 是一个字典，它包含了从 Python 开始运行起，被导入的所有模块。
  将每个 Python 类都拥有一个内置的类属性 __module__，它定义了这个类的模块的名字。它与 sys.modules 字典复合使用，你可以得到定义了某个类的模块的引用。 
- os.path 模块有几个操作文件和目录的函数。::

      os.path.join(os.path.expanduser("~"), "Python") 
      (filepath, filename) = os.path.split("c:\\music\\ap\\mahadeva.mp3") 
      (filename, extname) = os.path.splitext(filename)
      os.listdir("c:\\music\\_singles\\")

  在 Windows 和 Mac OS 下，normcase 将把整个文件名转换为小写字母；而在 UNIX 兼容的系统下，它将返回未作修改的文件名。
- glob 模块，另一方面，接受一个通配符并且返回文件的或目录的完整路径与之匹配。::

        import glob
        glob.glob('c:\\music\\*\\*.mp3')


第七章：正则表达式
----------------------------

- 导入正则表达式模块 ``import re``
- ``re.sub('ROAD$', 'RD.', s)`` 对字符串 s 进行搜索，满足正则表达式 'ROAD$' 的用 'RD.' 替换。
- ``re.search(pattern, 'MMMM')`` 函数试图匹配正则表达式。如果发现一个匹配，search 函数返回一个拥有多种方法可以描述这个匹配的对象，如果没有发现匹配，search 函数返回一个 None。
- 松散正则表达式：::

      pattern = """
              ^                   # beginning of string
              M{0,3}              # thousands - 0 to 3 M's
              (CM|CD|D?C{0,3})    # hundreds - 900 (CM), 400 (CD), 0-300 (0 to 3 C's),
                                  #            or 500-800 (D, followed by 0 to 3 C's)
              (XC|XL|L?X{0,3})    # tens - 90 (XC), 40 (XL), 0-30 (0 to 3 X's),
                                  #        or 50-80 (L, followed by 0 to 3 X's)
              (IX|IV|V?I{0,3})    # ones - 9 (IX), 4 (IV), 0-3 (0 to 3 I's),
                                  #        or 5-8 (V, followed by 0 to 3 I's)
              $                   # end of string
              """
      re.search(pattern, 'MCMLXXXIX', re.VERBOSE)  # 这里的re.VERBOSE参数就是告诉引擎这是一个松散的正则表达式，它会忽略空白符和注释。

- 如果一个正则表达式被用到很多次，就应该使用re.compile()函数来加速::

      phonePattern = re.compile(r'^(\d{3})-(\d{3})-(\d{4})$')
      phonePattern.search('800-555-1212').groups()

- Python中的正则与大部分语言中的还是很像的，简要的列一下：

  - ^ 匹配字符串的开始。
  - $ 匹配字符串的结尾。
  - \\b 匹配一个单词的边界。
  - \\d 匹配任意数字。
  - \\D 匹配任意非数字字符。
  - x? 匹配一个可选的 x 字符 (换言之，它匹配 1 次或者 0 次 x 字符)。
  - x* 匹配0次或者多次 x 字符。
  - x+ 匹配1次或者多次 x 字符。
  - x{n,m} 匹配 x 字符，至少 n 次，至多 m 次。
  - (a|b|c) 要么匹配 a，要么匹配 b，要么匹配 c。
  - \(x\) 一般情况下表示一个记忆组 (remembered group)。你可以利用 re.search 函数返回对象的 groups() 函数获取它的值。


第八章：HTML处理
----------------------------

- SGMLParser 将 HTML 分析成 8 类数据，然后对每一类调用单独的方法。由于Python中所有的类方法都可以视为虚方法，所以通过继承自SGMLParser就可以重定义处理每类数据时的方法。::

      from sgmllib import SGMLParser 
      class URLLister(SGMLParser):
          def reset(self):                              
              SGMLParser.reset(self)
              self.urls = []
          def start_a(self, attrs):                     
              href = [v for k, v in attrs if k=='href']  
              if href: self.urls.extend(href)

  像 SGMLParser 这样的分析器，技术术语叫做消费者 (consumer)。这种feed一个数据，然后通过子类覆盖父类的方法来实现功能是python中常用的一个手段。
- urllib 模块最简单的使用是提取用 urlopen 函数取回的网页的整个文本。urlopen 的返回值是像文件一样的对象。::

      import urllib                                       
      sock = urllib.urlopen("http://diveintopython.org/") 
      htmlSource = sock.read()
      sock.close()

- Python 有两个内置的函数，locals 和 globals，它们提供了基于 dictionary 的访问局部和全局变量的方式。
  在 locals 与 globals 之间有另外一个重要的区别：“locals 是只读的，globals 不是”。
- 基于 dictionary 的字符串格式化：::

      params = {"server":"mpilgrim", "database":"master", "uid":"sa", "pwd":"secret"}
      "%(pwd)s" % params        

  输出：'secret'


第九章：XML处理
----------------------------

- 处理 XML 有两种基本的方式：

  - 一种叫做 SAX (“Simple API for XML”)，就是类似于SGMLParser处理HTML时的feed方式；
  - 另外一种就是DOM的形式，这种在以前已经见过很多了。

- 包不过是模块的目录；嵌套包是子目录。一个包 (或一个嵌套包) 中的模块也只是 .py 文件罢。
- 导入一个包：导入模块很容易理解，但是包也可以导入，包只是普通的目录，如何导入呢？
  答案就是“一个包是一个其中带有特殊文件 __init__.py 的目录”，于是导入一个包实际上就是导入这个特殊命名的文件。
  __init__.py可以只是空文件，但必须存在；如果不存在，目录就仅仅是一个目录，而不是一个包，就不能被导入或者包含其它的模块和嵌套包。
- 载入一个 XML 文档:::

      from xml.dom import minidom
      xmldoc = minidom.parse('~/diveintopython/common/py/kgp/binary.xml')
      print xmldoc.toxml()

  一些常用的方法：xmldoc.childNodes, xmldoc.firstChild, pNode.firstChild.data
- 使用Unicode字符串： ``s = u'La Pe\xf1a'``
      以某种编码格式输出： ``print s.encode('latin-1')``
      或设置全局的默认编码格式： ``sys.setdefaultencoding('iso-8859-1')``
- 指定.py文件的编码::

      #!/usr/bin/env python
      # -*- coding: UTF-8 -*-

- getElementsByTagName 可能是XML处理时最好用的函数了，它“递归的”搜索整个文档，返回所有匹配的Node的列表。
  注意它是“递归的”搜索是很重要的。
- 访问元素属性，假设bitref是一个搜索得到的结点Node对象，常用的方法有如下：

  - bitref.attributes
  - bitref.attributes.keys()
  - bitref.attributes.values()
  - bitref.attributes["id"]
  - bitref.attributes["id"].name
  - bitref.attributes["id"].value


第十章：脚本和流
----------------------------

::

    def openAnything(source):                  
        if source == "-":    
            import sys
            return sys.stdin

            # try to open with urllib (if source is http, ftp, or file URL)
        import urllib                         
        try:                                  
            return urllib.urlopen(source)      
        except (IOError, OSError):            
            pass                              

        # try to open with native open function (if source is pathname)
        try:                                  
            return open(source)                
        except (IOError, OSError):            
            pass                              

        # treat source as string
        import StringIO                       
        return StringIO.StringIO(str(source))

**总结：这和C++中的template中的鸭子原理非常的像啊！返回的对象都拥有read()的方法，然后我们就可以调用它的read()方法，并不要求它们都符合某个接口，只要它们用起来的时候真的有read()就可以了。不需要显式的约束，只需要隐式的约束，降低了耦合性！**

- StringIO.StringIO(a_string) 常用来把一个字符串转换为一个类文件对象，你可用它做类文件的所有事情。比如 read 可以返回原始字符串。
  这个类文件对象支持read(), seek(), tell(), read(5)等操作。
- 标准输出、错误：sys.stdout, sys.stderr        
- print 语句的快捷语法： ``print >> sys.stderr, 'entering function'`` 
  可以用于写入任何打开的文件 (或者是类文件对象)。在这里，你可以将单个 print 语句重定向到 stderr 而且不用影响后面的 print 语句。
- __class__ 是每个 Python 对象的一个内置属性，__name__ 是每个 Python 类的内置属性，是一个字符串。
  所以，可以使用object.__class__.__name__来得到object对象的的类名的字符串表示，这在使用反射进行分发时非常常见。
- 处理命令行参数：

  - 对于简单的命令行参数，可以直接使用sys.argv来对参数进行访问；
  - 对于复杂的命令行参数，使用getopt模块来进行。::

      try:                                
              opts, args = getopt.getopt(argv, "hg:d", ["help", "grammar="]) 
      except getopt.GetoptError:           
              usage()                          
              sys.exit(2)   

    getopt模块定义了一套类似于printf的语法规则来解释命令行参数。


第十一章：HTTP Web服务
----------------------------

- 最简单的方法从HTTP获取内容：::

    import urllib
    data = urllib.urlopen('http://diveintomark.org/xml/atom.xml').read()    
    print data

- HTTP可以设置非常多的特征，这里介绍了5个，都可以通过urllib2轻松的做到：

  - 用户代理 (User-Agent)
  - 重定向 (Redirects)
  - Last-Modified/If-Modified-Since
  - ETag/If-None-Match
  - 压缩 (Compression)

- 使用gzip解压缩数据：::

    import gzip, StringIO
    compresseddata = f.read()
    compressedstream = StringIO.StringIO(compresseddata)
    gzipper = gzip.GzipFile(fileobj=compressedstream)
    data = gzipper.read()
    print data

  注意这里必须使用一个StringIO来做为缓冲，因为gzip 压缩的工作方式所致，GzipFile 需要存储其位置并在压缩文件上往返游走。


第十二章：SOAP Web服务
----------------------------

::

    from SOAPpy import WSDL

    # you'll need to configure these two values;
    # see http://www.google.com/apis/
    WSDLFILE = '/path/to/copy/of/GoogleSearch.wsdl'
    APIKEY = 'YOUR_GOOGLE_API_KEY'

    _server = WSDL.Proxy(WSDLFILE)
    def search(q):
        """Search Google and return list of {title, link, description}"""
        results = _server.doGoogleSearch(
            APIKEY, q, 0, 10, False, "", False, "", "utf-8", "utf-8")
        return [{"title": r.title.encode("utf-8"), "link": r.URL.encode("utf-8"), "description": r.snippet.encode("utf-8")}
                for r in results.resultElements]

- SOAP远不止于调用远程函数，比如 SOAP 还允许单向异步的信息通过，以及面向文档的 Web 服务。但书中只讨论了“RPC-style” SOAP。
- 这里使用的3个用于SOAP的库都不是python预装的，需要额外的去安装：PyXML、fpconst 和 SOAPpy 
- 可以看到，基本的使用方法就是：

  - 首先用swdl文件定义了SOAP的约定；
  - 再用WSDL.Proxy(SWDLFILE)把约定文件中的SOAP服务反射出来；
  - 于是，就可以像一个普通函数一样进行调用了。


第十三章：单元测试 & 第十四章：测试优先编程
-----------------------------------------------------

- 单元测试是以测试为核心开发策略的重要组成部分。如果你要写单元测试代码，尽早 (最好是在被测试代码开发之前) 开发并根据代码开发和需求的变化不断更新是很重要的。单元测试不能取代更高层面的功能和系统测试，但在开发的每个阶段都很重要：

  - 代码开发之前，强迫你以有效的方式考虑需求的细节。（我觉得第1点尤其有用！以用户的角度去思考非常重要！）
  - 代码开发中，防止过度开发。通过了所有测试用例，程序的开发就完成了。
  - 重构代码时，确保新版和旧版功能一致。（这点也非常重要，可以放心大胆地去重构，我以前总担心重构会引入新的BUG）
  - 在团队开发时，可以使你有信心，保证自己提交的代码不会破坏其他人的代码，因为你可以先运行其他人的单元测试代码。

- Python 有一个单元测试框架，被恰如其分地称作 unittest 模块，完整的单元测试流程如下：

  - 编写测试用例的第一步就是继承 unittest 模块中的 TestCase 类，它提供了很多可以用在你的测试用例中来测试特定情况的有用方法。
  - 每个独立测试本身都是一个方法，既不需要参数也不返回任何值。如果该方法正常退出没有引发异常，测试被认为通过；如果测试引发异常，测试被认为失败。
  - unittest 模块中的 TestCase 类提供了 assertRaises 方法，它接受这几个参数：预期的异常、测试的函数，以及传递给函数的参数。
  - 运行脚本将会执行 unittest.main()，由它来执行每个测试用例，也就是所有在刚才定义的继承自TestCase类中定义的方法。::

      if __name__ == "__main__":
          unittest.main()

    用命令行选项 -v 运行unittest.main()可以得到更详细的输出信息，这样你就可以看到每一个测试用例的具体运行情况。


第十五章：重构
----------------------------

- 全面的单元测试带来的最大好处不是你的全部测试用例最终通过时的成就感；也不是被责怪破坏了别人的代码时能够证明自己的自信。
  **最大的好处是单元测试给了你自由去无情地重构。**
- 单元测试是一个强大的概念，使用得当的话既可以减少维护成本又可以增加长期项目的灵活性。同样重要的是要意识到单元测试并不是“灵丹妙药”，也不是“银弹”。编写好的测试用例很困难，保持其更新更需要磨练 (特别是当顾客对修复严重的 Bug 大呼小叫之时)。单元测试不是其它形式测试的替代品，比如说功能性测试、集成测试以及可用性测试。但它切实可行且功效明显，一旦相识，你会反问为什么以往没有应用它。
- 很多语言都有单元测试框架，都要求你理解相同的基本概念：

  - 测试用例的设计方针是目的单一、可以自动运行、互不干扰。
  - 在被测试代码编写之前 编写测试用例。
  - 编写测试有效输入的测试用例并检查正确的结果。
  - 编写测试无效输入的测试用例并检查正确的失败。
  - 为描述 Bug 或反映新需求而编写和升级测试用例。
  - 为改进性能、可伸缩性、可读性、可维护性和任何缺少的特性而无情地重构。


第十六章：函数编程
----------------------------

- 回归测试（regression test），所谓的回归测试就是运行当前目录下所有的单元测试。::

      import sys, os, re, unittest
      def regressionTest():
              path = os.path.abspath(os.path.dirname(sys.argv[0]))   
              files = os.listdir(path)                               
              test = re.compile("test\.py$", re.IGNORECASE)          
              files = filter(test.search, files)                     
              filenameToModuleName = lambda f: os.path.splitext(f)[0]
              moduleNames = map(filenameToModuleName, files)         
              modules = map(__import__, moduleNames)                 
              load = unittest.defaultTestLoader.loadTestsFromModule  
              return unittest.TestSuite(map(load, modules))          
      if __name__ == "__main__":                   
              unittest.main(defaultTest="regressionTest")

- 内建 filter 函数，它接受两个参数：一个函数和一个列表，返回一个列表。作为第一个参数传递给 filter 的函数本身应接受一个参数，filter 返回的列表将会包含被传入列表参数传递给 filter 所有可以令函数返回真 (true) 的元素。
- 为什么用filter、map的方式比使用for循环的方式要更好：通常这是一个程序观问题，使用 map 和 filter 强迫你围绕数据进行思考，而不是去纠结于细节。
- 动态导入模块（动态导入模块最重要的就是__import__函数）： ::

      sys = __import__('sys')
      modules = map(__import__, moduleNames)
      
  - __import__ 函数与 import 语句的既定目标相同，但它是一个真正的函数，并接受一个字符串参数。
  - 变量 sys 现在是 sys 模块，和 import sys 的结果完全相同。

- 通过以下语言告知unittest模块调用它们的单元测试功能：::

      load = unittest.defaultTestLoader.loadTestsFromModule  
      return unittest.TestSuite(map(load, modules)) 


第十七章：动态函数
----------------------------

- 将函数当作对象，把它们存于列表中，把它们赋值给变量，并通过变量来调用它们：::

      def buildRule((pattern, search, replace)):                                        
              return lambda word: re.search(pattern, word) and re.sub(search, replace, word) 
      def plural(noun, language='en'):                             
              lines = file('rules.%s' % language).readlines()          
              patterns = map(string.split, lines)                      
              rules = map(buildRule, patterns)                         
              for rule in rules:                                      
                      result = rule(noun)                                  
                      if result: return result            

  于是，通过map把一系列的lambda函数映射到了一个列表里，于是可以通过这个列表来进行函数调用，这种新用法很爽啊。
  注意：这里同时还使用了“闭包”技术，在书上居然叫闭合。通过闭包技术，产生的lambda函数还能动态的使用传递给它的参数。
- 生成器 (Generator) ，在C#和Java等新的语言里这种技术已经见过很多了。::

      def rules(language):                                                                 
              for line in file('rules.%s' % language):                                         
                      pattern, search, replace = line.split()                                      
                      yield lambda word: re.search(pattern, word) and re.sub(search, replace, word)
      def plural(noun, language='en'):      
              for applyRule in rules(language): 
                      result = applyRule(noun)      
                      if result: return result 

  生成器技术只有两个关键点：

    - 使用yield标示这是一个生成器，函数会在每次yield之后暂停执行并等待下次调用；
    - 可以使用for item in generator来使用生成器，这在其它语言中已经见过很多次了。

  一个很好的用处就是可以使用生成器来动态的生成lambda函数，给for循环使用。


第十八章：性能优化
----------------------------

- 开始做性能优化之前，需要记住三点：

      - 你真的确信你需要优化吗？大部分代码并不需要优化的。
      - 你确信已经完成代码编写了吗？ 过早的优化就像是在一块半生不熟的蛋糕上撒糖霜。
      - 最关键的一点：在开始性能优化之前你需要一个完全的单元测试集。你最不需要的就是在乱动你的算法时引入新的问题。

- Python 社区有句俗语：“Python 自己带着电池。” 别自己写计时框架。Python 2.3 具备一个叫做 timeit 的完美计时工具::

      import timeit
      t = timeit.Timer("soundex.soundex('Pilgrim')", "import soundex")
      t.timeit()
      min(t.repeat(3, 2000000))

  timeit 模块定义了接受两个参数的 Timer 类。两个参数都是字符串。第一个参数是你要计时的语句，这里你计时的是以'Pilgrim'参数调用 Soundex 函数。传递给 Timer 的第二个参数是为第一个参数语句构建环境的导入语句。从内部讲，timeit 构建起一个独立的虚拟环境，手工地执行建立语句 (导入 soundex 模块)，然后手工地编译和执行被计时语句 (调用 Soundex 函数)。
- 理论上来说，正则表达式的效率肯定不会很高的，但是对于python来说：正则表达式引擎以 C 语言编写，被编译后则能本能地在你的计算机上运行，所以它有可能产生更好的效率。        
- 使用内置函数规则：如果 Python 有一个特殊函数，通过使用它做到了一个和你的工作差不多的事情。就用它并继续吧！
- 性能并不是一切。你在优化方面的努力应该与程序的可读性和可维护性相平衡。
- 性能优化的几个重要方面，这里是就 Python 而言，但它们却普遍适用。

  - 如果你要在正则表达式和编写循环间抉择，选择正则表达式。
  - 如果你需要在正则表达式和字符串方法间抉择，选择字符串方法。它们都是以 C 编译的，所以选取简单的。
  - 字典查找的通常应用很快，但是 string.maketrans 之类的特殊函数和 isalpha() 之类的字符串方法更快。如果 Python 有定制方法给你用，就使它吧！
  - 别太聪明了。有时一些明显的算法是最快的。
  - 不要太迷恋性能优化，性能并不是一切。

