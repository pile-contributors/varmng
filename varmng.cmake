
# enable/disable cmake debug messages related to this pile
set (VARMNG_DEBUG_MSG OFF)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (varmngInit
          use_mode)

    # default name
    if (NOT VARMNG_INIT_NAME)
        set(VARMNG_INIT_NAME "VarMng")
    endif ()

    # compose the list of headers and sources
    set(VARMNG_HEADERS
        "varmng.h"
        "varmng-const.h"
        "vareval.h"

        "interface/varctx_interface.h"
        "interface/varvalue_interface.h"
        "interface/vardef_interface.h"
        "interface/varbase_interface.h"

        "inmem/varfactory_inmem.h"
        "inmem/varctx_inmem.h"
        "inmem/vardef_inmem.h"
        "inmem/varvalue_inmem.h"

        "models/varctx_model.h"
        "models/vardef_model.h"
        "models/vareval_model.h"

        "delegates/varctx_delegate.h"
        )

    set(VARMNG_SOURCES
        "varmng.cc"
        "vareval.cc"

        "interface/varctx_interface.cc"
        "interface/varvalue_interface.cc"
        "interface/vardef_interface.cc"

        "inmem/varfactory_inmem.cc"
        "inmem/varctx_inmem.cc"
        "inmem/vardef_inmem.cc"
        "inmem/varvalue_inmem.cc"

        "models/varctx_model.cc"
        "models/vardef_model.cc"
        "models/vareval_model.cc"

        "delegates/varctx_delegate.cc"
        )

    set(VARMNG_QT_MODS
        "Core"
        "Gui"
        "Widgets"
        )

    pileSetSources(
        "${VARMNG_INIT_NAME}"
        "${VARMNG_HEADERS}"
        "${VARMNG_SOURCES}")

    pileSetCommon(
        "${VARMNG_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${use_mode}"
        ""
        "management"
        "Qt")

endmacro ()
