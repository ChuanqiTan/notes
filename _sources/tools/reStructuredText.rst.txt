.. |RST| replace:: \ *re*\ Structured\ *Text*\ 
.. |ITxt| replace:: Interpreted Text

.. role:: raw-html(raw)
   :format: html
.. default-role:: raw-html

.. highlight:: rest




.. sidebar:: 文档结构

    .. contents:: 



.. _RST-study-notes:

====================================
|RST| 学习笔记
====================================

.. _RST-study-notes-information:

.. include:: /head.template



Introduction
--------------

.. note:: 首先介绍 |RST| 的历史吧 。。。。。

.. rubric:: 参考资料

- `reStructuredText 官方主页 <http://docutils.sourceforge.net/rst.html>`_

  - User Documentation

    - [OK] `A reStructuredText Primer <http://docutils.sourceforge.net/docs/user/rst/quickstart.html>`_
    - [OK] `Quick reStructuredText <http://docutils.sourceforge.net/docs/user/rst/quickref.html>`_
    - [OK] `reStructuredText Cheat Sheet <http://docutils.sourceforge.net/docs/user/rst/cheatsheet.txt>`_

  - Reference Documentation

    - [OK] `An Introduction to reStructuredText <http://docutils.sourceforge.net/docs/ref/rst/introduction.html>`_
    - [OK] `reStructuredText Markup Specification <http://docutils.sourceforge.net/docs/ref/rst/restructuredtext.html>`_ 
      详细的语言规范，已用来完善其它部分的笔记
    - [OK] `reStructuredText Directives <http://docutils.sourceforge.net/docs/ref/rst/directives.html>`_
    - [OK] `reStructuredText Interpreted Text Roles <http://docutils.sourceforge.net/docs/ref/rst/roles.html>`_

  - Developer Documentation

    - `A Record of reStructuredText Syntax Alternatives <http://docutils.sourceforge.net/docs/dev/rst/alternatives.html>`_
    - `Problems With StructuredText <http://docutils.sourceforge.net/docs/dev/rst/problems.html>`_

  - How-To's

    - `Creating reStructuredText Directives <http://docutils.sourceforge.net/docs/howto/rst-directives.html>`_
    - `Creating reStructuredText Interpreted Text Roles <http://docutils.sourceforge.net/docs/howto/rst-roles.html>`_

- `Sphinx 官方主页 <http://sphinx-doc.org/index.html>`_

  - [OK] `Sphinx documentation contents <http://sphinx-doc.org/contents.html>`_



A |RST| Primer
----------------

- |RST| 里最重要的概念就是 **"段"** ，什么是 _`段的定义` ：
    "**左边对齐的一段文本，中间不能有空行**"，

- 常用的 **Inline Markup** 有 ``*italics*`` 、 ``**bold**`` 、 ````fixed-space```` 三种。
  与大多数编程语言类似， |RST| 使用 ``\`` 来做特殊字符的转义。

- |RST| 中的标记是不能叠加的，这的确很不方便，以后有可能会修正吧。
    \`\`...\`\`中的任何字符都会被原样输出，如``*text*``的结果是 ``*text*``\ ，里面的text不会产生强调的效果。

- 列表为分很多种：枚举列表(enumerated)、项目列表(bulleted)、定义列表(definitions)、 `Filed Lists`_ 、 `Option List`_ 。

  - 枚举列表很直观；可以理解为手动的项目列表吧::

      a. 数字
      b. 字母
      c. 小写字母

    效果如下:

    a. 数字
    b. 字母
    c. 小写字母

  - 项目列表也很直观，它使用 **"-"、"+"、"*"** 三种符号开头；自动项目列表，如果使用 `#.` 来开头，则会自动进行数字的编号::

      - first
      - second

      #. first
      #. sencod

    - first
    - second

    #. first
    #. sencod

  - "定义列表"，一般用来解释一个术语的::

      术语 : will display italics : classifier
        具体的解释内容...

    效果如下：

    术语 : will display italics : classifier
      具体的解释内容...
      
    术语的关键2点是: **术语不能太长只能有一行**、 **解释内容要缩进** ，很少有其它文章提到了术语不能超过一行的限制。
    
    如果术语很长，那就是普通的 **段缩进语法** 了，区别在于 *定义列表不空行，因此不分段也就不会产生段之间的比较大的间隔* ::
  
      第一段
  
          第二段
              
              第三段
  
    第一段
  
        第二段
            
            第三段

- 使用"::"来输出大段的代码，有2种用法：

  - 一是在一个段落的最后，这样会在段落的最后产生单个字符:，并把下一个段落视为代码落；
  - 二是另换一个新的段落单独写::， **这样就不会产生最后的单字符:输出** ，也是把下一个段落视为代码段落；

  同样，记得要缩进。再次强调一遍， |RST| 里和Python一样， **对齐缩进是非常重要的** ！

- Section的下划线字符只要是non-alphanumeric字符都可以，但常用的是= - ` : ' " ~ ^ _ * + # < >

  而整个document的title和subtitle一般会额外的修饰出来，就像这样::

    ================
    Document Title
    ================
    ----------
    Subtitle
    ----------

    Section Title
    =============

- _`插入一张图片` ::

    .. image:: ../_static/head.jpg
       :height: 369
       :width: 260
       :scale: 50
       :alt: alternate text
       :align: center

  效果如下：

  .. image:: ../_static/head.jpg
     :height: 369
     :width: 260
     :scale: 50
     :alt: alternate text
     :align: center



Quick |RST|
-------------

- 内置标记( Inline Markup )：

  =============================   =========================================================================================
  Plain text                      Typical result & Notes
  =============================   =========================================================================================
  ``*emphasis*``                  *emphasis* 斜体, 完整形式为 ``:emphasis:`emphasis```
  
  ``**strong**``                  **strong** 黑体, 完整形式为 ``:strong:`strong```

  ```text```                      `text` 默认的 |ITxt| ，完整的使用 |ITxt| 的方式为 ``:role:`text```

  ````inline literal````          ``inline literal`` 等宽体显示，一般用来显示代码的 ``:literal:`text```

  ``reference_``                  simplereference_  仅限一个单词的简单引用。 
                                    _`simplereference` target

  ```phrase reference`_``         `phrase reference`_ 短词引用，可以使用`...`来包括一段文字而不仅限于一个单词了。
                                    _`phrase reference` target

  ``anonymous__``                 匿名引用，双下划线结束的是匿名引用，省去了命名的烦恼， **匿名引用+间接引用** 示例::

                                      Python_ is `my favourite programming language`__.

                                      .. _Python: http://www.python.org/

                                      __ Python_

                                  效果如下：

                                  Python_ is `my favourite programming language`__.

                                  .. _Python: http://www.python.org/

                                  __ Python_

  ``_`internal target```          内部交叉引用的target，与reference搭配的。
                                      target 不区分简单引用 和 短语引用，都要用\`\`包含起来。

                                  另外一种语法就是 `内部超链接`_

  ``|substitution|``              _`替换引用` 能够替换文本、图片、链接、或者其它任何东西的组合，功能强大，好用无比！::

                                    .. |RST| replacement:: \ *re*\ Structured\ *Text*\ 
                                    |RST| is a good tool to write

                                  的效果为： |RST| is a gool tool to write

  ``脚注 [1]_``                   [1][2]为数字脚标、[#]为自动数字脚标、[*]为自动符号脚标::
                                  
                                    Here is a footnote [1]_ [#second_footnote]_ [*]_.
                                 
                                    .. [1] First footnote.

                                    .. [#second_footnote] A footnote and second_footnote_.

                                    .. [*] Third footnote
                                  
                                  效果如下：
                                            
                                    Here is a footnote [1]_ [#second_footnote]_ [*]_.
                                 
                                    .. [1] First footnote.

                                    .. [#second_footnote] A footnote and second_footnote_.

                                    .. [*] Third footnote
                                  
  ``参考引用 [CIT2002]_``         一般用以表示参考引用的形式，示例代码如下::
                                  
                                     Here is a citation ref [CIT1]_, here is same CIT1_.
                                  
                                     .. [CIT1] a citation referenct.
                                  
                                  效果如下：
                                     
                                     Here is a citation ref [CIT1]_, here is same CIT1_.
                                  
                                     .. [CIT1] a citation referenct.

  ``http://docutils.sf.net/``     http://docutils.sf.net/ 孤立的网址会自动生成链接。

                                  还可以显示为特定的文字 ```sohu <http://www.sohu.com>`_`` `sohu <http://www.sohu.com>`_
  =============================   =========================================================================================

- _`Filed Lists` ：一般用来显示文本的版本、作者等信息。会生成一个表格来显示内容，左边显示Filed Title，右边显示Detail::

    :Author: Tan Chuan Qi
    :Version: 1.0

  效果如下：

  :Author: Tan Chuan Qi
  :Version: 1.0

- _`Option List` 用来显示命令行参数(所以说 |RST| 是程序员专用啊)::

    -v           An option
    -o file      Same with value
    --delta      A long option
    --delta=len  Same with value

  效果如下：

  -v           An option
  -o file      Same with value
  --delta      A long option
  --delta=len  Same with value

- **行块(line blocks)** ：使用"|"字符来标记段内换行，因为 |RST| 中默认段内不换行，所以"|"标记一定要知道。

- Doctest 块：用来表示 **交互会话** 的代码，使用"``>>>``"开头，并且首尾处要以一个空行来标识。
  效果如下：

  >>> print "This is a doctest block."   
  This is a doctest block.

- 分隔符：连续4个以上的-,~,=等字符放在首尾空行之间，会显示为一个分行符::

    ---------

  效果如下：

---------

- 超链接：（分清与引用链接的区别，引用链接使用[]来表示，它的链接定义处不需要用:号，而超链接使用``来表示，one-word可省略，定义处要用:号）

  - 外部超链接::
     
      External hyperlinks, like Python_
      
      .. _Python: http://www.python.org/

    External hyperlinks, like Python_
    
    .. _Python: http://www.python.org/

  - _`内部超链接` （这种使用 ``.. _internal_link:`` 形式指定的内部超链接很重要，因为 **它的链接名不会显示** ，
    即下面例子中的链接目标中的"example"字符不会显示，这很有用！）::

      Internal hyperlinks, like example_
      
      .. _example: This is an example target.

    Internal hyperlinks, like example_
    
    .. _example:

    This is example    

- **隐式超链接** ：所有的section title, footnotes, citations都会自动的产生一个hyperlink target，所以可以直接去链接它们。
  如 `Introduction`_

- **指示（Directives）** ：是 |RST| 中强大的扩展机制，用来对 |RST| 引擎下达一个命令。
  最常用途就是插入一幅图片，参考 `插入一张图片`_

- **替换引用** ：类似于内嵌的指令，可以用来替换文本、图片等任意结构。前面已经有了 `替换引用`_ 的示例，下面举例替换图片::

    .. |image_substitution| image:: ../_static/head.jpg
       :scale: 20

    |image_substitution|

  .. |image_substitution| image:: ../_static/head.jpg
     :scale: 20

  |image_substitution|

- 注释：任何以..标记开始，但不使用任何指令结构的文本，都视为注释，如::

    .. This is comment.

    .. 

       This is comment too!



|RST| Directives
-----------------------------------------

- **Directive** 是 |RST| 中最核心的扩展机制，所有的扩展功能都是由Directive来定义的，Directives 的标准语法为::

    .. directive type :: directive
       block

- **Admonitions（告诫）** ，包括这几种： ``attention``, ``caution``, ``danger``, ``error``, ``hint``, ``important``, ``note``, ``tip``, ``warning``, ``admonition`` 。
  其中admonition是最普通的告诫，会同时设置它的Title和class=admonition-Title::

    .. admonition:: And, by the way...

       You can make up your own admonition too.

- 有2种插入图片的Directives，分别是 **Image和Figure** 。
  它们的区别在于： **Figure可以拥有对图片的说明文字** ::

    .. figure:: ../_static/head.jpg
       :scale: 20 %
       :alt: map to buried treasure

       This is the caption of the figure (a simple paragraph).

       This is detail.

  .. figure:: ../_static/head.jpg
     :scale: 20 %
     :alt: map to buried treasure
  
     This is the caption of the figure (a simple paragraph).

     This is detail

- **topic** ，一般用来描述一段 **独立的section** ::

    .. topic:: Topic Title

       This is detail

  topic似乎只能在无缩进的情况下使用:

.. topic:: Topic Title

   This is detail

- **sidebar** 用来显示侧边栏，比较常用的。

- **parsed literal** ：与普通literal block的等宽处理不同在于， **这里的内容依然会被parse** ，也就是说会生成的交叉链接等等::

      .. parsed-literal::

         Introduction_ , **Hello World**

  .. parsed-literal::

     Introduction_ , **Hello World**

  在普通的literal block中，由于 |RST| 的标签是不能叠加的。
  所以 ````Introduction_ ,**Hello World**```` 的结果为 ``Introduction_ , **Hello World**`` 。

- **code** : |RST| 自带的code比较弱，没有语法高亮，所以Sphinx为它扩展了code-block Directive::
  
      .. code:: python

         def my_function():
              "just a test"
                   print 8/2


  效果如下：

  .. code:: python

     def my_function():
          "just a test"
               print 8/2

- **math** : 它会进行Latax形式的数学公式翻译::

      .. math::

         α_t(i) = P(O_1, O_2, … O_t, q_t = S_i λ)

  .. math::

     α_t(i) = P(O_1, O_2, … O_t, q_t = S_i λ)

- **rubric** : 显示为类似于Title，最大的特点在于 **rubric 生成的是与文档章节无关的标题，即不会成为文档章节结构的一部分** 。
  经常有这个需求，比如本文中的 RST-study-notes-information_ 。

- **compound** : 把文字合并成一段（参考前面 `段的定义`_ ），段中不能有空行，这个Directive会把中间有空行的也视为一段。
  可以看作是一个方便书写的工具，为了成为一段而不换行，有时可能会显的布局局促::

    .. compound::

       The 'rm' command is very dangerous.  If you are logged
       in as root and enter ::

          cd /
          rm -rf *

       you will erase the entire contents of your file system.

  .. compound::

     The 'rm' command is very dangerous.  If you are logged
     in as root and enter ::

        cd /
        rm -rf *

     you will erase the entire contents of your file system.

- **container** : ``.. container:: custom`` 会把它的所属内容用一个container标签包含起来，并设置classes="custom"

- **\*-table** : ``table``, ``csv-table``, ``list-table`` 用来创建不同形式的 **带Title的表格** .

- **contents** : ``.. contents:: :depth: 2`` 用来显示文档的结构。

- **sectnum** : 把 ``.. sectnum::`` 放在文档的开头，会自动设置文档中结构的编号，以1, 1.1, 1.1.1的形式来设置。

- ``header`` 和 ``footer`` ，用来设置 **打印时** 的头和尾。

- **target-notes** : ``.. target-notes::`` 把文档中所有 ``.. _Python:: http://xx.xx.xx``
  形式的外部链接都集中显示为原来的链接地址形式，效果如下：

    .. target-notes::

- **meta** : 用来设置生成的HTML的Meta内容形式。

- **replace 替换** : 前面讨论了 `替换引用`_ ，这里看一个高级技巧实现 **链接替换** 形式::

      I recommend you try |Python|_.

      .. |Python| replace:: Python, *the* best language around
      .. _Python: http://www.python.org/

  I recommend you try |Python|_.

  .. |Python| replace:: Python, *the* best language around
  .. _Python: http://www.python.org/

- **Unicode 替换** ，代码和效果如下::

      .. |copy| unicode:: 0xA9

      Copyright |copy| 2003

  .. |copy| unicode:: 0xA9

  Copyright |copy| 2003

- **时间日期 替换** : 这非常有用，可以自动设置文章的最后更新时间，其默认的格式为： ``%Y-%m-%d`` ::

    .. |current-time| date:: %Y-%m-%d %H:%M:%S

    当前时间为: |current-time|

  .. |current-time| date:: %Y-%m-%d %H:%M:%S

  当前时间为: |current-time|

- **include** :  **方便的包含另一个文本文件** ，可以设置起始行、是否视为代码、是否显示行数等其它强大的功能。

- **raw** : 危险而强大的指令::

      .. raw:: html

         <hr width=50 size=10>

  上面代码表示html引擎在处理这段文本时不会做任何操作而原样输出。
  还可以设置 ``:file:``, ``:url:`` 选择文本来源，以及设置 ``:encoding:`` 来设置编码格式。

- **class** ：它会设置后面的第一个non-comment element的class属性，如这样设置：
  ``.. class:: exceptional remarkable``

- **Common Options** : 绝大多数Directives都支持这2个Option， ``class`` 和 ``name`` ：

  - ``class`` ：设置它们的class属性，与class Directive类似；
  - ``name``  ：设置生成引擎所生成的元素的name属性，看下面这个例子::

      .. image:: bild.png
         :name: my picture

    等价于::

      .. _my picture:

      .. image:: bild.png




|RST| Interpreted Text Roles
-----------------------------------------

- **最重要是的区分清楚2个概念：** |ITxt| 和 Directive

  - |ITxt| 的语法为 ``:role:`text``` 或 ```text`:role:`` ，功能是把text根据role规则进行Interprete（解释）；
  - Directive 的语法为 ``.. directive:: detail`` ，功能是发出一个特殊的指令。

- 最简洁的使用 |ITxt| 的方法就是 ```text``` ，这样实际上是在调用 **默认的role** ，默认的role为 ``title-reference`` ；
    **default-role** 指令可以设置默认role，如： ``.. default-role:: subscript`` 。

- ``:title:`Titles``` 和 ```Title`:title:`` 就是2种完整的调用 |ITxt| 的方式，它们完全没有区别，完全在于自己的喜好。

- | **创建一个新的role，是通过发出一个指令（Directive）来实现的** 。这也正好是区分 |ITxt| 和Directive的最佳例子吧 :)

  ::

    .. role:: role-name(base)
       :option: value

  | 这段代码显示了基于base role，创建一个新的role，当然base不是必须的。
  
    .. glossary:: 
      它的工作原理其实很简单:

        - 就是给这个role interprete的text添加class="rule-name"，如果设置了class option，就会覆盖为class="class-option"。
        - 它会使用base的HTML标签（无base时就使用inline标签） 。

  | 一般都是简单的基于现有的role，设置一下属性产生一个新的role；完全创建一个新的role需要编写它的python代码。

- **创建一个新role，也是设置现有role option的方式** ，如这样定义特定语言的code role::

    .. role:: latex(code)
       :language: latex

    :latex:`this is latex code`

  以及下面的 `default role 扩展`_ 也是最好的例子，非常非常常用，所以肯定要明白咯。

- | 使用 _`default role 扩展` |RST| 的功能：
  | 使用 |RST| 时，经常郁闷它没有下划线、删除线、字体、颜色等基础功能。
    虽然这些功能对于写一篇文档来说也不一定是必须的，但是，对于许多习惯了"富功能"编辑器的人来说，非常的不习惯。
    所以，这里就告诉你一种能够简洁快速的实现这些功能的方法，非常爽快！哈哈！

    ::

      .. role:: raw-html(raw)
         :format: html
      .. default-role:: raw-html

      `<U>` 下划线 `</U>` 、 `<S>` 删除线 `</S>` 

  | 它的生成效果为： `<U>` 下划线 `</U>` 、 `<S>` 删除线 `</S>` 、有了HTML，一些皆有可能！

- 常用的Standard Roles：

  :emphasis:        强调，也就是斜体字，也就是 ``*text*`` 。
  :literal:         字面值，使用等宽字体，也就是 ````text```` ，设置class="docutils literal"。
  :code:            可以表示各种语言的代码，与:literal:类似但不完全相同。
                    还可以设置language来指定特定的语言，设置class="code docutils literal"。
  :math:            应该是使用Latex来生成公式，还会修饰class="math"。
  :pre-reference:   可缩写为 ``:PEP:`` ，生成http://www.python.org/peps/pep-0287.html系列的链接 :PEP:`287` 。
  :rfc-reference:   可缩写为 ``:RFC:`` ，与PEP非常类似。
  :strong:          非常强调，也就是黑体，也就是 ``**text**`` 。
  :subscript:       可缩写为 ``:sub:`` ，生成下标。
  :superscript:     可缩写为 ``:sup:`` ，生成上标。
  :title:           全拼为 ``:title-reference:`` ，使用cite标签设置title，貌似也不常用。
  :raw:             **特殊的role** ，危险而强大的工具， **raw role不能直接使用，只能作为基类来使用** ，
                    而且建议所有派生自raw的role都使用raw-\*的命名方式。
                    直接输出HTML就是raw的一个经典使用方式::

                      .. role:: raw-html(raw)
                         :format: html



.. _sphinx-munal:

Sphinx 使用手册
-------------------------

- Sphinx 中的路径形式：
  
  - 如果不以 ``/`` 开头，就是相对当前文档的路径；
  - 如果以 ``/`` 开头，就是相对于源目录的路径。

- Sphinx 中添加的 **最重要的指令就是** ``.. toctree::`` 它能够把多份 |RST| 文档联合在一起，形成一份完整的文档::

    .. toctree::

       intro
       All about strings <strings>

  使用的是不包含扩展名的部分文件名，还可以使用这样 ``All about strings <strings>`` 指定标题名。
  它的常用option为：

  - ``:numbered:`` 显示章节编号；
  - ``:maxdepth: 2`` 文档结构最大显示深度，默认为全部显示；
  - ``:titlesonly:`` 仅显示title；
  - ``:glob:`` 匹配指令，所以满足glob的文档都会被匹配到，并以字母顺序排列；
  - ``:hidden:`` 文档被包含在文档结构中，但是不会显示在目录树中；

- 预留名字, 试图创建这些名字的文档会产生错误:  ``genindex``, ``modindex``, ``search``, ``以_开头的`` 。

- 段落级别的标记：它们的用途大多数都一目了然： ``.. versionadded::``, ``.. versionchanged::``, ``.. deprecated::``, ``.. seealso::``, ``.. centered::``, ``.. hlist::`` 。
  
  其中 ``.. hlist::`` 是用来生成水平列表. 它将列表项横向显示并减少项目的间距使其较为紧凑::

    .. hlist::
       :columns: 3

       * 列表
       * 的子
       * 项会
       * 水平
       * 排列

  .. hlist::
     :columns: 3
  
     * 列表
     * 的子
     * 项会
     * 水平
     * 排列

- **术语** : ``.. glossary::`` 该指令必然包含一个reST式的定义列表标记，由术语和定义组成. 这些定义其后可被 term 引用::

      .. glossary::

         environment
            一个结构，包含信息是所有文档的保存路径，使用的参考文献等.
            在解析的阶段使用，因此连续运行时仅需解析新的或修改过的文档.

      :term:`environment`

  .. glossary::

     environment
        一个结构，包含信息是所有文档的保存路径，使用的参考文献等.
        在解析的阶段使用，因此连续运行时仅需解析新的或修改过的文档.

  :term:`environment`

- 语法显示 ``.. productionlist::`` 可以用来展示满足BNF（巴科斯范式）的语法，这个应该非常不常用。

- **默认语法高亮** ``.. highlight:: cpp`` : 会设置默认语法高亮为C++语言直到遇到下一个 ``highlight`` 指令。
  这太常用了，除python文档外，肯定需要先设置这个默认语法高亮的::

    .. highlight:: cpp
       :linenothreshold: 5

  如果代码块多于5行将产生行号.

- 还可以使用 ``.. code-block::`` 来追加各种语法高亮，代码如下::

    .. code-block:: python
        :linenos:  #显示行号
        :emphasize-lines: 1,3

        def foo():
            print "Love Python, Love FreeDome"
            print "E文标点,.0123456789,中文标点,. "

  效果如下：

  .. code-block:: python
      :linenos:   
      :emphasize-lines: 1,3

      def foo():
          print "Love Python, Love FreeDome"
          print "E文标点,.0123456789,中文标点,. "

- **包含外部代码文件** ``.. literalinclude::`` 示例如下::

    .. literalinclude:: example.rb
       :language: ruby
       :emphasize-lines: 12,15-18
       :linenos:
       :encoding: latin-1
       :pyobject: Timer.start
       :lines: 1,3,5-10,20-

  其它的一些选项如： ``tab-width``, ``prepend``, ``append``, ``start-after``, ``end-before`` 。

  同时注意：标准包含指令 .. include , 如果文件不存在会抛出异常. 这一个则仅会产生警告.

- 另一个 **非常重要的Sphinx扩展** 就是 ``ref role`` ，它可以实现 **跨文档** , **自动改变文本** 的交叉链接.
  它有2种使用形式,首先是对章节标题可以自动获取要显示的文本::

    .. _sphinx-munal

    Sphinx 使用手册
    --------------------------

    :ref:`sphinx-munal`.

  效果就是这样: :ref:`sphinx-munal` , 但是对于非章节标题,就需要手动设置它的显示文本::

    .. _beautiful_ref:

    hello world

    :ref:`hello world <beautiful_ref>`

  .. _beautiful_ref:

  hello world

  :ref:`hello world <beautiful_ref>`

  自动实现 **跨文档** + **自动适应改变文件** 足以让我们使用这个漂亮的扩展代替 |RST| 的原始交叉引用 ```Text <target>`_`` 了.

- 还有非常多 _`Sphinx扩展的role` , 我觉得常用的有:

  - ``:term:`` 术语索引. 术语由指令 glossary 创建,这个与glossary搭配使用很有用. :term:`environment` 
  - ``:abbr:`` 简写形式,这还蛮有用的,尤其是与replacement搭配使用. :abbr:`LIFO (last-in, first-out)` 
  - ``:doc:`` 链接到指定文档
  - ``:option:`` 执行程序的命令行参数. 需包含连字号开头. 产生到指令 ``.. option::`` 的链接.
  - ``:envvar:`` 环境变量. 会生成索引.

  以下可能用到的机会比较少:

  - ``:download:`` 可被下载的文档
  - ``:token:`` 语法名子 (用来产生到指令 productionlist 的链接).
  - ``:keyword:`` Python的关键字. 会创建这些关键字的链接.
  - ``:command:`` 系统级别的命令 :command:`rm`  
  - ``:dfn:`` 在文本中标记术语定义. (不产生索引条目)
  - ``:file:`` 文件或目录名. 可以使用花括号指示变量部分
  - ``:guilabel:`` 表示用户交互接口的标签
  - ``:kbd:`` 标记键值序列
  - ``:mailheader:`` RFC 822-样式邮件头的名字
  - ``:makevar:`` 命令 make 的变量名
  - ``:manpage:`` 参考 Unix 手册页
  - ``:menuselection:`` 菜单选项
  - ``:mimetype:`` MIME 类型
  - ``:newsgroup:`` Usenet 新闻组
  - ``:program:`` 执行程序脚本
  - ``:regexp:`` 正则表达式 :regexp:`^\\w+$`
  - ``:samp:`` 一块字面量文本
  - ``:pep:`` 对Python Enhancement Proposal 的参考, 产生外部链接
  - ``:rfc:`` Internet Request for Comments的参考, 产生外部链接

- **三种默认定义的替换** ，可在配置文件里设置

  .. parsed-literal::

      release is **|release|**, version is **|version|**, today is **|today|**.

  release is |release|, version is |version|, today is |today|.

- ``.. sectionauthor:: name <email>``, ``.. codeauthor:: name <email>`` 设置当前章节或当前代码段的作者.
  只有在 ``show_authors`` 设置为真时,它们才会产生输出.

- **显式的创建index** : Sphinx 会为所有 ``glossary``, ``PEP``, ``RFC`` 自动的生成index,
  还可以使用 ``.. index::`` 手动的生成 index, 生成的index都可以在 ``index`` 页面被找到. 示例如下::

    .. index:: paragraph

  .. index:: paragraph

  然后就可以这样 ``:index:`paragraph``` :index:`paragraph` 来创建引用,
  并在 `index 页面 <../genindex.html>`_ 页面可以看到任一index item的所有引用.

- **根据变量决定内容** : 这对程序员来说是最喜欢的功能了, if 语句嘛::

    .. only:: (html and (latex or draft)) 

        display when condition is true!

  未定义的标签为假, 定义的为真 (使用 -t 命令行参数或者在文件 conf.py 中定义).

- **Domain 是 Directives 和 Roles 的集合, 用来描述一些对象和显示它们的交叉链接** , 常用的用途当然还是编程语言中的对象.
  官方定义如下:

  *A domain is a collection of markup (reStructuredText directives and roles) to describe and link to objects belonging together, e.g. elements of a programming language.*

  它们的用途一目了然, 用来书写编程语言中的对象实在是太方便了::

      .. py:function:: format_exception(etype, value, tb[, limit=None])

         Format the exception with a traceback.

         :param etype: exception type
         :param value: exception value
         :param tb: traceback object
         :param limit: maximum number of stack frames to show
         :type limit: integer or None
         :rtype: list of strings

  .. py:function:: format_exception(etype, value, tb[, limit=None])

     Format the exception with a traceback.

     :param etype: exception type
     :param value: exception value
     :param tb: traceback object
     :param limit: maximum number of stack frames to show
     :type limit: integer or None
     :rtype: list of strings

  并可以这样轻松的实现交叉引用: ``:py:func:`format_exception``` :py:func:`format_exception` .
  只能说Sphinx用来写代码文档真是太漂亮太爽了.
  
  **要知道, 默认的domain是py** , 其它的内置Domain是 ``py``, ``c``, ``cpp``, ``js``, ``rst`` .
  Python Domain中的支持是相当完善的, 其它的语言也挺不错, c和cpp下所支持的对象如下:

  - C 语言

    - ``.. c:function:: type name(signature)``
    - ``.. c:member:: type name``
    - ``.. c:macro:: name``
    - ``.. c:type:: name``
    - ``.. c:var:: type name``
    - ``:c:data:``
    - ``:c:func:``
    - ``:c:macro:``
    - ``:c:type:``

  - C++ 语言

    - ``.. cpp:class:: signatures``
    - ``.. cpp:function:: signatures``
    - ``.. cpp:member:: signatures``
    - ``.. cpp:type:: signatures``
    - ``.. cpp:namespace:: namespace``
    - ``:cpp:class:``
    - ``:cpp:func:``
    - ``:cpp:member:``
    - ``:cpp:type:``

    引用C++模板类时, 由于 ``:cpp:class:`MyClass<T>``` 会解释成以MyClass的Title去引用T, 所以需要特殊处理一下,写成 ``:cpp:class:`MyClass\<T>```.

    当引用C++中的重载函数等对象时,可以提供完整的签名以区分重载对象. 注意当引擎无法区分要引用那个重载对象时,会选择第1个对象.

- **Standard Domain** 就是无名Domain, 其中包含一些常用的指令, 如:

  - ``.. program:: name``
  - ``.. option:: name args, name args, ...`` 使用方式如下:: 

        .. program:: rm
        
        .. option:: -r
        
           Work recursively.

        :option:`rm -r`

    .. program:: rm
    
    .. option:: -r
    
       Work recursively.

    :option:`rm -r`
  - ``.. envvar:: name`` 描述一个环境变量, 可以通过 ``:envvar:`` 来引用, 参考 `Sphinx扩展的role`_
  - ``.. describe:: text``
  - ``.. object:: text`` 这2个指令比较类似,而且 **都不会产生index** , 它们的使用方式和效果如下::

      .. object:: Object

         Details...

      .. describe:: Describe

         Details...

    .. object:: Object
    
       Details...
    
    .. describe:: Describe
    
       Details...
