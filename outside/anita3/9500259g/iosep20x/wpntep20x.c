
#include "../ioscarrier/ioscarrier.h"
#include "iosep20x.h"

/*
{+D}
    SYSTEM:             Library Software
       
    MODULE NAME:        wpntep20x() - write output point
                            
    VERSION:            A
    
    CREATION DATE:      04/01/09
    
    CODED BY:           FJM
        
    ABSTRACT:           Module writes an output value to a single I/O point.
    
    CALLING SEQUENCE:   status = wpntep20x(ptr, port, point, value);
                          where:
                            status (long)
                              The returned error status.
							ptr (pointer to structure)
							  Pointer to the configuration block structure.
                            port (unsigned)
                              The target I/O port number.
                            point (unsigned)
                              The target I/O point number
                            value (unsigned)
                              The output value.
                            
    MODULE TYPE:        long
    
    I/O RESOURCES:
    
    SYSTEM RESOURCES:   

    MODULES CALLED:
    
    REVISIONS:
    
      DATE      BY      PURPOSE
    --------   -----    ---------------------------------------------------
    
{-D}
*/


/*  
    MODULES FUNCTION DETAILS

        This module writes a value (0 or 1) to a point of an output port.
        The valid values of "port" are 0 to 2 and "point" are from 0 to 15.
        Otherwise, a -1 is returned.
*/
    
long wpntep20x(c_blk, port, point, value)

struct cblkep20x *c_blk;
unsigned port;              /* the I/O port number */
unsigned point;             /* the I/O point of a port */
unsigned value;             /* the output value */

{

/*
    DECLARE LOCAL DATA AREAS:
*/

    word bpos;		    /* bit position */
    word temp;

/*
    ENTRY POINT OF ROUTINE
*/

    if (port > 2 || point > 15 || value > 1)    /* error checking */
       return(-1);
 
    bpos = 1 << point;
    value <<= point;
    temp = input_word( c_blk->nHandle, (word*)&c_blk->brd_ptr->io_port[port]);
    output_word( c_blk->nHandle, (word*)&c_blk->brd_ptr->io_port[port], ((temp & ~bpos) | value) );
    return(0);
}
