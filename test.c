#include <stdio.h>

#include "src/jyggalog.h"

// hook for fatal exiting
void bye(void){
    printf("Bye bye!\n");
}

int main(void){
    
    // set formatting style
    jl_set_style(JL_STYLE_COLORS | JL_STYLE_FILE_NAME | JL_STYLE_LINE_NUMBER);   
    jl_set_fatal_hook(bye);
    jl_log(JL_DEBUG,"It's debugin' time");
    jl_log(JL_INFO,"I'm info");
    
    jl_log(JL_WARN,"I'm a warn");

    jl_set_level(JL_WARN);
    jl_log(JL_INFO,"I'm other info");

    jl_logf(JL_ERROR,"it's fuck%dd man",3);

    jl_log(JL_FATAL,"It's dead chat");
    
    return 0;
}
