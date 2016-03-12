
# enable/disable cmake debug messages related to this pile
set (VARMNG_DEBUG_MSG ON)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (varmngInit
          ref_cnt_use_mode)

    # default name
    if (NOT VARMNG_INIT_NAME)
        set(VARMNG_INIT_NAME "VarMng")
    endif ()

    # compose the list of headers and sources
    set(VARMNG_HEADERS
        "varmng.h")
    set(VARMNG_SOURCES
        "varmng.cc")

    pileSetSources(
        "${VARMNG_INIT_NAME}"
        "${VARMNG_HEADERS}"
        "${VARMNG_SOURCES}")

    pileSetCommon(
        "${VARMNG_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${ref_cnt_use_mode}"
        ""
        "category1"
        "tag1;tag2")

endmacro ()
