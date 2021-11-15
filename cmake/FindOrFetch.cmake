Include( FetchContent )

macro( FindOrFetch #[[LibName FetchOptions...]] )
    find_package( ${ARGV0} CONFIG )
    if( NOT ${ARGV0}_FOUND )
        FetchContent_Declare( ${ARGV} )
        FetchContent_MakeAvailable( ${ARGV0} )
    endif( )
endmacro( )
