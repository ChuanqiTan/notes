.. highlight:: cpp

Google C++ 库
====================

.. sidebar:: Google C++ Library

    | Google的开源的这些C++库，几乎已经成了业界标准，再加上公司里这些库的大规模应用。
    | 掌握这些库是有必要的！

.. include:: /head.template

gflags
---------------

- ``fgrep -l -f /var/tmp/foo johannes brahms`` 其中 ``-l,  -f /var/tmp/foo`` 是flags，而后面的 ``johannes brahms`` 叫做命令行参数；
- gflags支持的几种类型（三个参数：flag_name, default_name, help_string）：

  - DEFINE_bool: boolean
  - DEFINE_int32: 32-bit integer
  - DEFINE_int64: 64-bit integer
  - DEFINE_uint64: unsigned 64-bit integer
  - DEFINE_double: double
  - DEFINE_string: C++ string

- 与DEFINE_*对应的是DECLARE_*宏，相当于一处定义，多处声明；
    例如在foo.cc中进行DEFINE_string, 同时在foo.h中进行DECLARE_string，就可以像一个全局变量一样到处使用。
- 注意DEFINE_*和DECLARE_*宏都必须在全局的命名空间，gflags中其它的符号都是在google namespace下；
- RegisterFlagValidator函数可以用来注册参数的有效性检查函数，使用方案如下，一看就懂::

    static bool ValidatePort(const char* flagname, int value) {
      if (value > 0 && value < 32768)   // value is ok
        return true;
      printf("Invalid value for --%s: %d\n", flagname, (int)value);
      return false;
    }
    DEFINE_int32(port, 0, "What port to listen on");
    static const bool port_dummy = google::RegisterFlagValidator(&FLAGS_port, &ValidatePort);

- google::ParseCommandLineFlags(&argc, &argv, true); 一般在main函数的第一行用来初始化所有的参数，最后一个参数指定是否在函数返回时从argc, argv中清除已经处理过的参数；
- gflags支持多种形式的参数表达方式，但是Google推荐统一为--flag=value的形式，对于bool型的参数，统一为--flag, --noflag的形式，而且不支持例如ls -la这样将2个flags组合缩写的方式；
- 特殊的库自带的flags：

    --help          shows all flags from all files
    --helpfull      same as -help, but unambiguously asks for all flags (in case -help changes in the future)
    --helpshort     shows only flags for the file with the same name as the executable (usually the one containing main())
    --helpxml       like --help, but output is in xml for easier parsing
    --helpon=FILE   shows only flags defined in FILE.*
    --helpmatch=S   shows only flags defined in ``*S*.*``
    --helppackage   shows flags defined in files in same directory as main()
    --version       prints version info for the executable
    --undefok       默认情况下传入未知的命令行参数会引起程序ERROR退出，但可以指定--undefok=flag1, flag2来允许一些未知的命令行参数；
    
    ``--`` 会结束flag prase，后面的内容会被忽略，例如： ``foo -f1 1 -- -f2 2`` 的结果是只会处理-f1

- 从其它地方读取参数：

    --fromenv       从环境变量中读取flag
    --tryfromenv    和--fromenv的区别在于如果环境变量中没有定义，也不会引起fatal error
    --flagfile      非常好用的从文件读取flags

- 可以通过google::SetUsageMessage(), google::SetVersionString()来设置Usage和Version信息。但是，切记这2个函数必须在google::ParseCommandLineFlags()函数之前运行，否则无效；
- 还可以在#include <gflags/gflags.h>之前定义宏#define STRIP_FLAG_HELP 1来删除--help的信息；
    虽然gflags的官方文档这么写，但是目前的实验看来没有达到这个效果。

glog
------------------
- 首先glog是依赖于gflags的，常用的几个命令行参数必须要知道：

    --logtostderr                把所有的日志信息都输出到stderr上，默认是false，在公司的ybuild里已经设置成了默认true；
    --stderrthreshold            超过这个级别的日志除了输出到日志外，还输出到stderr；
    --minloglevel                超过这个级别的信息才进行记录；
    --log_dir                    当logtostderr为false时是输出到文件，这里指定输出目录，默认是/tmp/；
    --v                          对于VLOG(m)型的日志，最大的输出日志级别，有可能被vmodule覆盖；
    --vmodule                    分模块（文件名）指定VLOG(m)的最大日志级别，以字符串 ``<module patter1>=<log level1>,<module patter2>=<log level2>`` 的形式指定，支持通配符；

- LOG(m)的默认4个级别：INFO、WARNING、ERROR、FATEL；
- 常用的条件日志记录方式：LOG_IF, LOG_EVERY_N, LOG_IF_EVERY_N, LOG_FIRST_N；
- CHECK*家族：这些CHECK*宏非常好用，在判定失败时会生成一个FATAL级别的日志，并输出调用堆栈，非常有用；
    还可以用以字符串不敏感的进行字符串判等和double的判等。
- 在宏名前加D可以指定只在Debug模式下生效，如DLOG、DLOG_IF、DLOG_EVERY_N等等；
- **自定义级别宏VLOG(n)** ：自定义日志级别，在 ``--v=3`` 的参数影响下，将只输出级别<=3的日志。
    同样，自定义级别的VLOG宏（Verbose Logging, 详细日志）也支持VLOG_IF、VLOG_EVERY_N、VLOG_IF_EVERY_N等等；

  **非常非常有用，可以分等级查看不同详细程度的日志，尤其对于程序库来说，这太重要了，库几乎只能以VLOG(n)进行日志输出！**
- 当需要线程安全时，使用RAW_LOG、RAW_CHECK等；
- 系统级日志记录：使用SYSLOG、SYSLOG_IF、SYSLOG_EVERY_N宏，它们将调用syslog()函数来记录系统级别的日志；
- perror风格的日志，使用PLOG、PLOG_IF形式的宏能够在errno的状态及描述添加到日志中；
- 还可以定义GOOGLE_STRIP_LOG宏来清减glog的日志信息，剔出前面的那些日志级别、所在代码行数的信息::

    #define GOOGLE_STRIP_LOG 1    // this must go before the #include!
    #include <glog/logging.h>


gtest
------------------
- GTEST中的 **断言宏** 大概分为2种：

    - ASSERT_* 系列的断言，当检查点失败时，退出当前案例的执行。 
    - EXPECT_* 系列的断言，当检查点失败时，继续往下执行。
    - 还有一个 ``testing::StaticAssertTypeEq<int, T>();`` 可以用来检查类型T是不是int类型，否则产生一个编译时的静态断言错误。

  ::

    /*!
     * Author : chuanqi.tan@gmail.com
     */

    #include "gtest/gtest.h"
    #include <string>
    using namespace std;

    template<typename T>
    void ThrowIt(T const &t) {
      throw t;
    }

    /*!
     * 全部使用EXPECT_*断言，同时要知道与EXPECT_*对应ASSERT_*断言
     * 其实，几乎所有的断言都是可以用EXPECT_TRUE()来模拟的。
     */
    TEST(test, test) {
      EXPECT_TRUE(true);
      EXPECT_FALSE(false);

      EXPECT_EQ(1, 1);
      EXPECT_NE(1, 2);
      EXPECT_LT(1, 2);
      EXPECT_LE(1, 1);
      EXPECT_GT(2, 1);
      EXPECT_GE(2, 2);

      EXPECT_STREQ("abc", "abc");
      EXPECT_STRNE("ABC", "abc");
      EXPECT_STRCASEEQ("ABC", "abc");
      EXPECT_STRCASENE("bcd", "abc");

    //  ADD_FAILURE();
    //  FAIL();
    //  SUCCEED();

      EXPECT_THROW(ThrowIt(1), int);
      EXPECT_THROW(ThrowIt(string("abc")), string);
      EXPECT_ANY_THROW(ThrowIt(1));
      EXPECT_ANY_THROW(ThrowIt(string("abc")));
      EXPECT_NO_THROW(int(1));

      EXPECT_FLOAT_EQ(1.0000001, 1.00000001);
      EXPECT_DOUBLE_EQ(1.00000000000001, 1.00000000000001);
      EXPECT_NEAR(2, 3, 2);

      typedef int IntergetType;
      testing::StaticAssertTypeEq<int, IntergetType>();
    }

    int main(int argc, char **argv) {
      testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }


- **事件机制** ，参照dream/test/gtest/event.cc：

    - 全局的，所有案例执行前后。
    - TestSuite级别的，在 **某一批案例中第一个案例前，最后一个案例执行后** , 注意是 ``static void SetupTestCase(){}`` 。
    - TestCae级别的， **每个TestCase前后** , 注意是 ``virtual void Setup() {}`` 。
    - 参数化机制可以极大的减少代码，使得代码更简洁：

  ::

    /*!
     * Author : chuanqi.tan@gmail.com
     */

    #include "gtest/gtest.h"
    #include <iostream>

    /*!
     * 全局事件
     */
    class GlobalEvent : public testing::Environment {
     public:
      virtual void SetUp() {
        std::cout << "FooFooEnvironmentSetUP" << std::endl;
      }
      virtual void TearDown() {
        std::cout << "FooFooEnvironmentTearDown" << std::endl;
      }
    };

    /*!
     * TestSuit事件
     */
    class TestSuitEventTest : public testing::Test {
     protected:
      TestSuitEventTest() {
        value_ = 99;
      }

      static void SetUpTestCase() {
        std::cout << "SetUpTestCase of TestSuit" << std::endl;
      }
      static void TearDownTestCase() {
        std::cout << "TearDownTestCase of TestSuit" << std::endl;
      }

      int value_;
    };
    TEST_F(TestSuitEventTest, T1) {
      EXPECT_EQ(1, 1);
      std::cout << value_ << std::endl;
    }
    TEST_F(TestSuitEventTest, T2) {
      EXPECT_EQ(2, 2);
      std::cout << value_ << std::endl;
    }

    /*!
     * TestCase事件
     */
    class TestCaseEventTest : public testing::Test {
     protected:
      virtual void SetUp() {
        std::cout << "SetUp of TestCase" << std::endl;
      }
      virtual void TearDown() {
        std::cout << "TearDown of TestCase" << std::endl;
      }
    };
    TEST_F(TestCaseEventTest, T1) {
      EXPECT_EQ(1, 1);
    }
    TEST_F(TestCaseEventTest, T2) {
      EXPECT_EQ(2, 2);
    }
    TEST_F(TestCaseEventTest, T3) {
      EXPECT_EQ(3, 3);
    }

    int main(int argc, char **argv) {
      testing::AddGlobalTestEnvironment(new GlobalEvent());
      testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }

- **参数化机制** 可以极大的减少代码，使得代码更简洁，主要就是几步： 

  - 确定参数的类型，通过继承TestWithParam<T>来实现；
  - GetParm()得到当前传递过来的参数；
  - INSTANTIATE_TEST_CASE_P 宏注册test case。

  ::

    /*!
     * Author : chuanqi.tan@gmail.com
     */

    #include "gtest/gtest.h"
    #include <iostream>
    using namespace std;

    class IsPrimeParamTest : public ::testing::TestWithParam<int> {
    };

    TEST_P(IsPrimeParamTest, HandleTrueReturn) {
      int n = GetParam();
      EXPECT_TRUE(n % 2 == 1);
    }

    INSTANTIATE_TEST_CASE_P(TrueReturn1,
                            IsPrimeParamTest,
                            testing::Values(1, 3, 5, 7, 9, 11));

    vector<int> vec;
    INSTANTIATE_TEST_CASE_P(TrueReturn2,
                            IsPrimeParamTest,
                            testing::ValuesIn(vec));

    int main(int argc, char **argv) {
      for (int i = 1; i < 6; i += 2) {
        vec.push_back(i);
      }
      testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }

- **死亡测试** 通常在测试过程中，我们需要考虑各种各样的输入，有的输入可能直接导致程序崩溃，这时我们就需要检查程序是否按照预期的方式挂掉，这也就是所谓的 *死亡测试* 。
  gtest的死亡测试能做到在一个安全的环境下执行崩溃的测试案例，同时又对崩溃结果进行验证，使用 ``[ASSERT|EXPECT]_[DEATH|EXIT]`` 宏对崩溃的方式进行测试::

    /*!
     * Author : chuanqi.tan@gmail.com
     */

    #include "gtest/gtest.h"

    void Foo() {
      int *pInt = 0;
      *pInt = 42;
    }

    /*!
     * EXPECT_DEATH(statement, regex)在引起了DEAD，并且输出的ERROR信息匹配regex时才通过测试。
     */
    TEST(FooDeathTest,Demo) {
      EXPECT_DEATH(Foo(), "");
    }

    TEST(ExitDeathTest,Demo) {
      EXPECT_EXIT(_exit(1), testing::ExitedWithCode(1), "");
    }

    int main(int argc, char **argv) {
      testing::InitGoogleTest(&argc, argv);
      return RUN_ALL_TESTS();
    }

  **通过死亡测试的条件是：程序以EXPECT的方式崩溃，并且输出的stderr内容能够匹配regex**

  注意事项
      * 不要在死亡测试里释放内存。
      * 在父进程里再次释放内存。
      * 不要在程序中使用内存堆检查。

- **gtest的参数设置** 对于运行参数，gtest提供了三种设置的途径：
    :系统环境变量:      参数对应的大写，如gtest_output对应的环境变量为GTEST_OUTPUT
    :命令行参数:        ``--output=xml``
    :代码中指定FLAG:    ``testing::GTEST_FLAG(output) = "xml:"`` 
                        推荐将这句放置InitGoogleTest之前，这样就可以使得对于同样的参数，命令行参数优先级高于代码中指定。

  我常用的参数就是--gtest_filter, --gtest_output，完整的参数列表可以用 ``--help`` 得到，具体如下：
   --gtest_list_tests               使用这个参数时，将不会执行里面的测试案例，而是输出一个案例的列表。
   --gtest_filter                   对执行的测试案例进行过滤，支持通配符( ``?*-:`` )
   --gtest_also_run_disabled_tests  执行案例时，同时也执行被置为无效的测试案例。
   --gtest_repeat                   设置案例重复运行次数，非常棒的功能！
   --gtest_color                    (yes|no|auto)输出命令行时是否使用一些五颜六色的颜色，默认是auto。
   --gtest_print_time               打印每个测试案例的执行时间。
   --gtest_output                   将测试结果输出到一个xml中
   --gtest_break_on_failure         调试模式下，当案例失败时停止，方便调试
   --gtest_throw_on_failure         当案例失败时以C++异常的方式抛出
   --gtest_catch_exceptions         是否捕捉异常(windows下专用)

