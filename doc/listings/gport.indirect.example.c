#include <liquid/liquid.h>
// ...
{
    // create the port
    //     size :   1024
    //     type :   int
    gport2 p = gport2_create(1024,sizeof(int));

    // create buffer for writing
    int w[256];

    // producer writes data to w here

    // producer writes 256 values to port
    gport2_produce(p,(void*)w,256);

    // repeat as necessary

    // destroy the port object
    gport2_destroy(p);
}