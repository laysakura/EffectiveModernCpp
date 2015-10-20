# このレポジトリ

"Effective Mordern C++" を手を動かしながら読む。

# 動かし方

一部の項目で、Boostが必要なのでインストール。

```bash
brew install boost
```

使っているコンパイラが `-std=c++14` に対応していない場合はバージョンアップ。

```bash
brew tap homebrew/versions
brew install homebrew/versions/llvm36
```

あとはビルドして実行。

```bash
cmake .
```

コンパイラを明示的に指定する場合は

```bash
cmake -DCMAKE_CXX_COMPILER=/usr/local/bin/clang++-3.6 .
```

make

./item01
== f_case1_rT() ==
---
param's type: int&
T: int
...
```
