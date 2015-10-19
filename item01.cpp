//
// Created by Sho Nakatani on 2015/10/20.
//

#include <iostream>
#include <boost/type_index.hpp>

using namespace std;

// ケース1: ParamTypeが参照もしくはポインタだが、ユニヴァーサル参照ではない
// => 参照性が無視される
template<typename T>
void f_case1_rT(T& param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

template<typename T>
void f_case1_const_rT(const T& param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

template<typename T>
void f_case1_const_pT(T* param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

// ケース2: ParamTypeがユニヴァーサル参照である
// => exprが右辺値の場合はケース1と同様の規則
// => exprが左辺値の場合はTもParamTypeも左辺値参照と推論
template<typename T>
void f_case2_rrT(T&& param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

// ケース3: ParamTypeがポインタでも参照でもない
// => 参照性、const性が無視される
template<typename T>
void f_case3_T(T param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

// 配列実引数
// => 値渡しの場合: ポインタにdecayする
// => 参照渡しの場合: 配列の参照となる
template<typename T>
void f_array_argument_T(T param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

template<typename T>
void f_array_argument_rT(T& param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

// 関数実引数
// => 値渡しの場合: 関数ポインタにdecayする
// => 参照渡しの場合: 関数の参照となる
template<typename T>
void f_function_argument_T(T param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

template<typename T>
void f_function_argument_rT(T& param) {
  using boost::typeindex::type_id_with_cvr;
  cout << "---" << endl
  << "param's type: " << type_id_with_cvr<decltype(param)>().pretty_name() << endl
  << "T: " << type_id_with_cvr<T>().pretty_name() << endl;
}

void someFunc(int, double) {}

int main() {
  {
    cout << "== f_case1_rT() ==" << endl;
    int x = 0;
    const int cx = x;
    const int& rx = x;
    f_case1_rT(x);  // param's type: int&, T: int
    f_case1_rT(cx); // param's type: const int&, T: const int
    f_case1_rT(rx); // param's type: const int&, T: const int
    cout << endl;
  }
  {
    cout << "== f_case1_const_rT() ==" << endl;
    int x = 0;
    const int cx = x;
    const int& rx = x;
    f_case1_const_rT(x);  // param's type: const int&, T: int
    f_case1_const_rT(cx); // param's type: const int&, T: int
    f_case1_const_rT(rx); // param's type: const int&, T: int
    cout << endl;
  }
  {
    cout << "== f_case1_const_pT() ==" << endl;
    int x = 0;
    const int* px = &x;
    f_case1_const_pT(&x); // param's type: int*, T: int
    f_case1_const_pT(px); // param's type: const int*, T: const int
    cout << endl;
  }

  {
    cout << "== f_case2_rrT() ==" << endl;
    int x = 0;
    const int cx = x;
    const int& rx = x;
    f_case2_rrT(x);  // param's type: int&, T: int&
    f_case2_rrT(cx); // param's type: const int&, T: const int&
    f_case2_rrT(rx); // param's type: const int&, T: const int&
    f_case2_rrT(27); // param's type: int&&, T: int
    cout << endl;
  }

  {
    cout << "== f_case3_T() ==" << endl;
    int x = 0;
    const int cx = x;
    const int& rx = x;
    const char* const ptr = "Fun with pointers";
    f_case3_T(x);   // param's type: int, T: int
    f_case3_T(cx);  // param's type: int, T: int
    f_case3_T(rx);  // param's type: int, T: int
    f_case3_T(ptr); // param's type: const char*, T: const char*
    cout << endl;
  }

  {
    cout << "== f_array_argument_T() ==" << endl;
    const char name[] = "J. P. Briggs";
    f_array_argument_T(name); // param's type: const char*, T: const char*
    cout << endl;
  }
  {
    cout << "== f_array_argument_rT() ==" << endl;
    const char name[] = "J. P. Briggs";
    f_array_argument_rT(name); // param's type: const char(&)[13], T: const char[13]
    cout << endl;
  }

  {
    cout << "== f_function_argument_T() ==" << endl;
    f_function_argument_T(someFunc); // param's type: void (*)(int, double), T: void (*)(int, double)
    cout << endl;
  }
  {
    cout << "== f_function_argument_rT() ==" << endl;
    f_function_argument_rT(someFunc); // param's type: void (&)(int, double), T: void (int, double)
    cout << endl;
  }

  return 0;
}
