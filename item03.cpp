//
// Created by Sho Nakatani on 2015/10/20.
//

#include <iostream>
#include <deque>
#include <boost/type_index.hpp>

using namespace std;

#define PRINT_DECLTYPE(sym) \
  cout << "decltype(" << #sym << "): " \
  << boost::typeindex::type_id_with_cvr<decltype(sym)>().pretty_name() \
  << endl;


// decltypeでオブジェクトの型を見るための諸々定義
class Widget {};

bool f(const Widget& w);

template<typename T>
class myvector {
public:
  T& operator[](std::size_t index);
};

struct Point {
  int x;
};


void authenticateUser() {};

// 返り値型のautoの挙動を確かめるための関数。
// cの実引数にはstd::deque<int> dを与えるものとする。
// returnに与えられる式c[i]の評価結果はint&であるものの、
// 関数呼び出しの返り値は右辺値なので、authAndAccess(d, 5)の返り値は右辺値のintになる。
// 従って、authAndAccess(d, 5) = 10;のような代入コードはコンパイルエラーとなる。
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index&& i) {
  authenticateUser();
  return c[i];
}

// 返り値型のdecltype(auto)の挙動を確かめるための関数。
// cの実引数にはstd::deque<int> dを与えるものとする。
// returnに与えられる式c[i]の評価結果はint&であるため、
// 返り値の型であるdecltype(auto)は厳密にint&となる。
// 従って、authAndAccess(d, 5) = 10;はコンパイルが通る。
template<typename Container, typename Index>
decltype(auto) authAndAccess2(Container& c, Index&& i) {
  authenticateUser();
  return c[i];
}


int main() {
  {
    const int i = 0;
    PRINT_DECLTYPE(i);  // const int
  }

  {
    Widget w;
    const Widget &rw = w;
    PRINT_DECLTYPE(w);  // Widget
    PRINT_DECLTYPE(rw); // const Widget&
  }

  {
    Widget w;
    PRINT_DECLTYPE(f);     // bool(const Widget&)
    PRINT_DECLTYPE(f(w));  // bool
  }

  {
    PRINT_DECLTYPE(Point::x);  // int
  }

  {
    myvector<int> v;
    PRINT_DECLTYPE(v);     // myvector<int>
    PRINT_DECLTYPE(v[0]);  // int&
  }

  {
    std::deque<int> d{ 1, 2, 3, 4, 5 };
    PRINT_DECLTYPE(authAndAccess(d, 5));  // int(右辺値)
    //authAndAccess(d, 5) = 10;  // 右辺値への代入なのでコンパイルエラー

    PRINT_DECLTYPE(authAndAccess2(d, 5));  // int&
    authAndAccess2(d, 5) = 10;   // int&への代入はコンパイルが通る
  }

  {
    Widget w;
    const Widget& cw = w;

    auto myWidget1 = cw;  // p.12-13の「ケース3: 型指定子がポインタでも参照でもない」
    PRINT_DECLTYPE(myWidget1);  // Widget

    decltype(auto) myWidget2 = cw;
    PRINT_DECLTYPE(myWidget2);  // const Widget&
  }

  return 0;
}
