
    // fluid
    {
       forAll(fluidRegions, i)
       {
           forAll (thermoFluid[i].he(), cellI)
            {
                thermoFluid[i].he()[cellI] = hCell[fluidCellMap[i][cellI]];
            }

            thermoFluid[i].correct();
        }

    }

    // solid
    {
       forAll(solidRegions, i)
       {
           forAll (thermos[i].he(), cellI)
            {
                thermos[i].he()[cellI] = hCell[solidCellMap[i][cellI]];
            }
            thermos[i].correct();

        }
    }



