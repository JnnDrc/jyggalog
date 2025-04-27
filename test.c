#include <stdio.h>

#include "jyggalog.h"

int main(void){
    
    jl_set_style(JL_STYLE_COLORS | JL_STYLE_FILE_NAME | JL_STYLE_LINE_NUMBER | JL_STYLE_TIME | JL_STYLE_DATE);

    jl_log(JL_DEBUG,stdout,"It's debugin' time");
    jl_log(JL_INFO,stdout,"I'm info");
    jl_log(JL_WARN,stdout,"I'm a warn");
    jl_set_level(JL_WARN);
    jl_log(JL_INFO,stdout,"I'm other info");
    
    jl_logf(JL_ERROR,stdout,"it's fuck%dd man",3);

    jl_log(JL_FATAL,stdout,"It's dead chat");
    
    return 0;
}
