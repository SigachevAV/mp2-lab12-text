file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${TextLib} STATIC ${srcs} ${hdrs}) 