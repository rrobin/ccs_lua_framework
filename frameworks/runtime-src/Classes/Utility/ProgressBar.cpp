#include "ProgressBar.h"

barGoLink::~barGoLink()
{
    printf( "\n" );
    fflush(stdout);
}

barGoLink::barGoLink( int row_count )
{
    rec_no    = 0;
    rec_pos   = 0;
    indic_len = 50;
    num_rec   = row_count;
    empty     = " ";
    #ifdef _WIN32
    full      = "\x3D";
    #else
    full      = "*";
    #endif
    #ifdef _WIN32
    printf( "\x3D" );
    #else
    printf( "[" );
    #endif
    for ( int i = 0; i < indic_len; i++ ) printf( empty );
    #ifdef _WIN32
    printf( "\x3D 0%%\r\x3D" );
    #else
    printf( "] 0%%\r[" );
    #endif
    fflush(stdout);
}

void barGoLink::step( void )
{
    int i, n;

    if ( num_rec == 0 ) return;
    rec_no++;
    n = rec_no * indic_len / num_rec;
    if ( n != rec_pos )
    {
        #ifdef _WIN32
        printf( "\r\x3D" );
        #else
        printf( "\r[" );
        #endif
        for ( i = 0; i < n; i++ ) printf( full );
        for ( ; i < indic_len; i++ ) printf( empty );
        float percent = (((float)n/(float)indic_len)*100);
        #ifdef _WIN32
        printf( "\x3D %i%%  \r\x3D", (int)percent);
        #else
        printf( "] %i%%  \r[", (int)percent);
        #endif
        fflush(stdout);

        rec_pos = n;
    }
}
