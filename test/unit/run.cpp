#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include <libxml/parser.h> // for xmlInitParser(), xmlCleanupParser()

#if defined(HAVE_CAIRO)
#include <cairo.h>
#endif
#include <unicode/uclean.h>

#ifdef MAPNIK_USE_PROJ4
#include <proj_api.h>
#endif

int main (int argc, char* const argv[])
{
    int result = Catch::Session().run( argc, argv );
    // only call this once, on exit
    // to make sure valgrind output is clean
    // http://xmlsoft.org/xmlmem.html
    xmlCleanupParser();

#if defined(HAVE_CAIRO)
    // http://cairographics.org/manual/cairo-Error-handling.html#cairo-debug-reset-static-data
    cairo_debug_reset_static_data();
#endif

    // http://icu-project.org/apiref/icu4c/uclean_8h.html#a93f27d0ddc7c196a1da864763f2d8920
    u_cleanup();

#ifdef MAPNIK_USE_PROJ4
    // http://trac.osgeo.org/proj/ticket/149
 #if PJ_VERSION >= 480
    pj_clear_initcache();
 #endif
    // https://trac.osgeo.org/proj/wiki/ProjAPI#EnvironmentFunctions
    pj_deallocate_grids();
#endif

    return result;
}
