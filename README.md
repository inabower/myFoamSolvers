# myFoamSolvers

今までに作成したOpenFOAMのソルバーとユーティリティを統合した。動作しない場合もあるかも。

# SOLVERS

## residualSimpleFoam

- version : OpenFOAM-v4.1, OpenFOAM-v1806
- developed : https://github.com/inabower/OpenFOAM4.1-utilities , https://github.com/inabower/residualSimpleFoam
- description : 
  - simpleFoamに対してpEqnとUEqnの残差を場として出力する機能を追加したもの。
  - log(mag(残差))の値を出力している。

## chtGlobalEnergyPimpleFoam

- version : OpenFOAM-v3.0.1
- developed : https://github.com/inabower/OpenFOAM-3.0.1-solvers
- description : 
  - 詳細：https://qiita.com/inabower/items/35834f10cf366c5e0ef5
  - chtMultiRegion系のエネルギーの計算のみを全領域統合して行うもの
  - splitMeshRegionsで分割した場合に出力されるファイルを読み込んで使用する
  - 並列計算には対応していない


# UTILITIES

## faceDirection

- version : OpenFOAM-v4.1
- developed : https://github.com/inabower/OpenFOAM4.1-utilities
- description : 
  - 各patchの面方向の単位ベクトルを出力する。
  - ポスト用。

## reverseSurface

- version : OpenFOAM-v4.1
- developed : https://github.com/inabower/OpenFOAM4.1-utilities
- description : 
  - STLファイルの面の向きを反転させる。
  - `reverseSurface old.stl new.stl 0`だとそのままstlを出力。ただしcontrolDictのprecisionが用いられる。
  - `reverseSurface old.stl new.stl 1`だと全ての面が反転する。
  - SALOMEのSolid GroupをSTL出力すると反転したメッシュが作成される場合もあるため。

## manualDecomposition

- version : OpenFOAM-v4.1
- developed : https://github.com/inabower/OpenFOAM4.1-utilities
- description : 
  - decomposeParで分割する計算領域をより任意に分割するためのもの。
  - `manualDecomposition.C`の中身を対称のメッシュに合わせて書き換える形で使用する。
  - コンパイルして実行すると、各セルがどのCPUに分配されるのかを`cellDecomposition`というvolScalarFieldとして出力される。
  - decomposeParDictを以下のように変更して使用する。

```cpp
    numberOfSubdomains  8;
    method              manual;
    manualCoeffs
    {
        dataFile        "cellDecomposition";
    }
```

## functionProcessor

- version : OpenFOAM-v4.1
- developed : https://github.com/inabower/OpenFOAM4.1-utilities
- description : 
  - 上記の`manualDecomposition`をfunctionObjectとして実行するためのもの。
  - このプログラム自体はdecomposeParで読み込む`cellDecomposition`というファイルを出力するだけの機能を持つ。それをどのような内容にするのかについてを`codedFunctionObject`によって記述する。
  - `manualDecomposition`は分割ごとにwmakeして実行ファイルを作る必要があったが、これはcontrolDict内にその処理を記述できるため汎用性UP。
  - 毎回コンパイルするため、同じメッシュ同じ分割方法を実行する場合は`manualDecomposition`よりも遅い。

## makeDirection

- version : OpenFOAM-v1812
- developed : https://github.com/inabower/OpenFOAM_utilities
- description : 
  - `functionProcessor`と同じく`codedFunctionObject`を使う前提のもの。
  - refineMeshで分割する方向を指示するためのvectorFieldを出力する。

