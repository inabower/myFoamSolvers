# residualSimpleFoam
simpleFoam with output of residual fields..  
Verified with OpenFOAM v1806.  
This is a solver copied from simpleFoam.  

#### residual fields
- residual_p : initial residual of pEqn
- residual_U : initial residual of UEqn

They are outputs of fvMatrix::residual()

![residualSimpleFoam_sample](https://github.com/inabower/residualSimpleFoam/blob/master/test/residual.gif)

#### How to make

- cp simpleFoam
- Modify Make/files
- Create fields for residuals of p,U without dimensions
- Copy values of (p|U)Eqn.residual() to fields
