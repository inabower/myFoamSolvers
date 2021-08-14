// Write decomposition rules as you want.
// This is just example
// r       : processor number
// (x y z) : cell center position

if(x<0) r=0;
else    r=1;

if(y<0) r+=2;

if(z<0) r+=4;


/*
    // if using cellSet
    if(regionI == 0)
    {
        if(x<0) r=0;
        else    r=1;

        if(y<0) r+=2;

        if(z<0) r+=4;
    }
    else if(regionI == 1)
    {
        if(x<0) r=8;
        else    r=9;

        if(y<0) r+=2;

        if(z<0) r+=4;
    }
*/
