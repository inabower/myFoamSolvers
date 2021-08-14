### functionProcessor
This utility is to distribute the cells of your model to each processors as you want.
executionFile *functionProcessor.C* is just to make a field **0/cellDist** and a list **constant/cellDecomposition**.
You have to write *how to decompose* as code in your **system/controlDict**.

#### HOW TO USE

1. Enter your number of processors to calculate in **system/decomposeParDict** as *numberOfSubDomain*.
2. Modify a code as following in **system/controlDict**.
3. Execute `functionProcessor`.  (-overWrite and -region {regionName} are also OK).
4. Remove or hyde this functionObject in **system/controlDict** to execute your solver.
4. If the decomposition is OK, execute `decomposePar` and solve with your solver. (if you want to use as a region of the multiRegionModel, copy the **constant/polyMesh** direcory and **constant/cellDecomposition** file.)

#### CODE FORMAT
in **system/controlDict**
```
functions
{
    processor
    {
        libs ("libutilityFunctionObjects.so");
        type  coded;
        name  processor;

        codeEnd
        #{
            // your code
        #};
    }
}

```

#### CODE EXAMPLE
You can get a processor number field with the object named *cellDist* as volScalarField.
If you have modified this field, The list **constant/cellDecomposition** which is used to `decomposePar` is up-date.

```
    volScalarField& dist = const_cast<volScalarField&>
    (mesh().lookupObject<volScalarField>("cellDist"));

    forAll(dist, i)
    {
        const vector& C = mesh().C()[i];
        const scalar& x = C[0];
        const scalar& y = C[1];
        const scalar& z = C[2];

        scalar& d = dist[i];

        if(x>0) d=0;
        else    d=1;

        if(y>0) d+=2;

        if(z>0) d+=4;
    }
```
