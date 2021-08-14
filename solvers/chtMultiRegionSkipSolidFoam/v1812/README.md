# chtMultiRegionSkipSolidFoam
chtMultiRegionFoam which skip solving solid for each steps

# createSolidFields.H

```cpp
scalarList skipInterval(solidRegions.size(), -1.0);
scalarList integratedTime(solidRegions.size(), 0.0);
...

forAll(solidRegions, i)
{
	....
	
	const dictionary& solutionDict = solidRegions[i].solutionDict();
	if(solutionDict.found("skipInterval"))
	{
		skipInterval[i] = solutionDict.lookupOrDefault<scalar>("skipInterval", -1.0);
	}
}
```

# solveSolid.H

```cpp

forAll(solidRegions, i)
{
	Info<< "\nSolving for solid region "
		<< solidRegions[i].name() << endl;
	integratedTime[i] += runTime.deltaT().value();
	if(skipInterval[i] < integratedTime[i] || runTime.outputTime())
	{
		const scalar deltaTOrg = runTime.deltaT().value();
		runTime.deltaT().value() = integratedTime[i];
		
		#include "setRegionSolidFields.H"
		#include "readSolidMultiRegionPIMPLEControls.H"
		#include "solveSolid.H"
		
		runTime.deltaT().value() = deltaTOrg;
		integratedTime[i] = 0.0;
	}
	else
	{
		Info << "Skipped calculation" << endl;
	}
}
```

# progress

- 動くけど値が変わる
  - deltaTとステップ数の積和が違うことが原因？
  - deltaTを更新するようにしてもうまくいかない
  - もともとchtMultiRegionFoamはdeltaTで値が変わったけどこれもそのたぐいか？
  - 今回は0.1秒/output1秒とだいぶ荒くやった
- この誤差をチェックする
  - 流体のdeltaTをめっちゃ細かくするように調整
  - 個体は10ステップずつskipしてみる
  - --> よさげ
