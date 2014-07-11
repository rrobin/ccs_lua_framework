/* 
 
 */

#ifndef POCKETHERO_ERRORS_H
#define POCKETHERO_ERRORS_H

#define WPAssert( assertion ) { if( !(assertion) ) { fprintf( stderr, "\n%s:%i ASSERTION FAILED:\n  %s\n", __FILE__, __LINE__, #assertion ); assert( #assertion &&0 ); } }
#ifndef ASSERT
#define ASSERT WPAssert
#endif
#endif
