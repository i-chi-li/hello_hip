# hello-hip

simple-cpp は、動作する。
simple-cpp-openmp は、動作する。
simple-hip は、GPU 側のログが出ない。原因は未調査。

プロジェクトルートにある、CMakeLists.txt に定義している、
GPU_TARGETS の設定は、CPU 内臓の AMD Radeon(TM) Graphics の場合は、`gfx1036` と指定する必要がある。
`gfx1030` では、実行は出来るが、GPU 側の処理が行われない。
GPU 側の処理が正常に動作していれば、ログに `Hello World... from HIP thread = ` が出力される。

Toolchain: Visual Studio 2022

CMake options

```
-D CMAKE_C_COMPILER:PATH="${HIP_PATH}bin\clang.exe" -D CMAKE_CXX_COMPILER:PATH="${HIP_PATH}bin\clang++.exe"
```
