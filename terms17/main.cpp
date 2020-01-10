#include <iostream>
#include <memory>
using namespace std;

/*条款17 lazy evaluation缓式评估
 * 本条款列举了3种lazy evaluation的四种应用场景，其实最常用也最有参考意义的只是第三种
 * 第一种：写时复制，也就是真正的复制发生在对其中一个共享对象写入时
 * 第二种：区分读和写，比如判断用户对s[3]执行的操作是读取还是写入，只有在动作发生是才能判断出来
 * 第三种：见测试例子
 * 第四种：lazy expression evaluation表达式缓式评估，主要用于矩阵的运算，用户主要用于获得矩阵运算后的新矩阵某一处下标的结果，因此没必要对所有的下标进行计算，用户需要什么再计算什么
*/

namespace LazyEvaluation {

//大型的、可持久存在的对象，比如离线数据
class LargeObj
{
public:
    LargeObj(int id) : m_id(id), m_nm(nullptr), m_len(100) {}
    const string& name() const {
        if (m_nm == nullptr) {
            cout << __FUNCTION__ << endl;
            //只有当用户读到name时，再去离线文件中读取该数据，一般都不需要读，从而避免了计算，提高了效率
            m_nm = make_shared<string>("jijijijijijijiji");
        }
        return *m_nm;
    }
    int len() const {
        //对于必要的计算，如果使用lazy evaluation甚至会降低效率，因此，对于绝对必要的数据，还是采用eager evaluation为好
        return m_len;
    }
private:
    int m_id;
    mutable shared_ptr<string> m_nm;
    int m_len;
};

}

int main()
{
    LazyEvaluation::LargeObj a(10086);
    cout << a.name() << endl;
    return 0;
}
